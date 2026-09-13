// https://github.com/mono-1729/AtCoder_cpp/blob/main/library/beam/fast_beam.cpp
namespace fast_beam {

// ビーム探索中の盤面を識別する128ビットキー。
// 後の段階ではZobrist Hashを格納する。
struct StateKey {
    std::uint64_t low = 0;
    std::uint64_t high = 0;

    friend bool operator==(
        const StateKey&,
        const StateKey&
    ) = default;
};

// 64ビット整数のビットを十分に攪拌する。
// ハッシュテーブルのバケット番号を偏りにくくするために使う。
inline std::uint64_t mix64(std::uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

// 128ビットキーをハッシュテーブル用の64ビット値へ変換する。
inline std::uint64_t hash_key(const StateKey key) {
    return mix64(
        key.low ^ std::rotl(key.high, 27)
    );
}

// StateKeyから候補配列の添字を引く専用ハッシュテーブル。
// std::unordered_mapより用途を限定し、確保回数と定数倍を削減する。
class FlatIndexMap {
public:
    explicit FlatIndexMap(
        const std::size_t max_live_entries = 0
    ) {
        reserve(max_live_entries);
    }

    // 最大要素数に応じてテーブルを確保する。
    //
    // 使用率を25%以下に抑えることで、
    // 線形探索の連続距離を短くする。
    void reserve(const std::size_t max_live_entries) {
        std::size_t capacity = 8;

        while (capacity < max_live_entries * 4 + 1) {
            capacity *= 2;
        }

        entries_.assign(capacity, Entry{});
        stamps_.assign(capacity, 0);
        mask_ = capacity - 1;
        generation_ = 1;
    }

    // 全要素を論理的に削除する。
    //
    // 配列全体を0クリアせず、世代番号を進めるだけなのでO(1)。
    void clear() {
        ++generation_;

        // uint32_tが一周したときだけ物理的に初期化する。
        if (generation_ == 0) {
            std::fill(
                stamps_.begin(),
                stamps_.end(),
                0
            );
            generation_ = 1;
        }
    }

    // keyが存在すれば、その候補配列上の添字をvalueへ格納する。
    [[nodiscard]] bool find(
        const StateKey key,
        std::uint32_t& value
    ) const {
        std::size_t index = bucket(key);

        while (is_occupied(index)) {
            if (entries_[index].key == key) {
                value = entries_[index].value;
                return true;
            }

            index = (index + 1) & mask_;
        }

        return false;
    }

    // keyと候補配列上の添字を登録する。
    //
    // 衝突時は次のバケットを調べる線形探索法を用いる。
    void insert(
        const StateKey key,
        const std::uint32_t value
    ) {
        std::size_t index = bucket(key);

        while (is_occupied(index)) {
            if (entries_[index].key == key) {
                entries_[index].value = value;
                return;
            }

            index = (index + 1) & mask_;
        }

        entries_[index] = Entry{key, value};
        stamps_[index] = generation_;
    }

    // 指定したkeyを削除する。
    //
    // 線形探索法では単純に空きにすると、
    // 後ろにある要素をfindできなくなる場合がある。
    // そこで、削除位置より後ろの連続領域を挿入し直す。
    void erase(const StateKey key) {
        std::size_t index = bucket(key);

        while (
            is_occupied(index)
            && !(entries_[index].key == key)
        ) {
            index = (index + 1) & mask_;
        }

        assert(is_occupied(index));
        stamps_[index] = 0;

        index = (index + 1) & mask_;

        while (is_occupied(index)) {
            const Entry entry = entries_[index];

            stamps_[index] = 0;
            insert(entry.key, entry.value);

            index = (index + 1) & mask_;
        }
    }

private:
    struct Entry {
        StateKey key{};
        std::uint32_t value = 0;
    };

    // 容量は2の冪なので、剰余演算の代わりにANDを使える。
    [[nodiscard]] std::size_t bucket(
        const StateKey key
    ) const {
        return static_cast<std::size_t>(
            hash_key(key)
        ) & mask_;
    }

    [[nodiscard]] bool is_occupied(
        const std::size_t index
    ) const {
        return stamps_[index] == generation_;
    }

    std::vector<Entry> entries_;
    std::vector<std::uint32_t> stamps_;

    std::size_t mask_ = 0;
    std::uint32_t generation_ = 1;
};

// 問題固有情報をPayloadに格納する汎用候補。
//
// scoreは小さいほど良い。
// payloadには親ノード番号、操作、遷移長などを後から格納する。
template <class Payload>
struct Candidate {
    StateKey key{};
    std::int64_t score = 0;
    Payload payload{};
};

// pushの結果。
enum class PushStatus : std::uint8_t {
    Rejected,
    Inserted,
    ReplacedDuplicate,
    ReplacedWorst,
};

// 置換された候補をremovedで呼び出し側へ返す。
//
// 後の探索木では、removedの親ノードに対する
// 参照カウントを減らすために必要になる。
template <class CandidateType>
struct PushResult {
    PushStatus status = PushStatus::Rejected;
    std::optional<CandidateType> removed;

    [[nodiscard]] bool accepted() const {
        return status != PushStatus::Rejected;
    }
};

// 重複状態を除きながら、良い方から最大width個を保持する。
//
// 内部構造:
//   candidates_    実際の候補
//   index_         StateKey -> candidates_の添字
//   heap_          最悪候補が根に来る最大ヒープ
//   heap_position_ 候補添字 -> heap_上の位置
template <class Payload>
class TopKSelector {
public:
    using CandidateType = Candidate<Payload>;

    explicit TopKSelector(const std::size_t width)
        : width_(width),
          index_(width) {
        candidates_.reserve(width_);
        heap_.reserve(width_);
        heap_position_.reserve(width_);
    }

    [[nodiscard]] std::size_t size() const {
        return candidates_.size();
    }

    [[nodiscard]] bool empty() const {
        return candidates_.empty();
    }

    // 候補を追加する。
    //
    // 1. 同じStateKeyが存在する場合
    //    良い候補なら置換し、悪ければ棄却する。
    //
    // 2. まだwidth未満の場合
    //    そのまま追加する。
    //
    // 3. width個埋まっている場合
    //    現在の最悪候補より良い場合だけ置換する。
    [[nodiscard]] PushResult<CandidateType> push(
        CandidateType candidate
    ) {
        PushResult<CandidateType> result;

        if (width_ == 0) {
            return result;
        }

        std::uint32_t slot = 0;

        // 同じ状態がすでに保持されている場合。
        if (index_.find(candidate.key, slot)) {
            if (!better(candidate, candidates_[slot])) {
                return result;
            }

            result.status =
                PushStatus::ReplacedDuplicate;

            result.removed.emplace(
                std::move(candidates_[slot])
            );

            candidates_[slot] =
                std::move(candidate);

            fix_heap(slot);
            return result;
        }

        // まだビーム幅に空きがある場合。
        if (candidates_.size() < width_) {
            slot = static_cast<std::uint32_t>(
                candidates_.size()
            );

            candidates_.push_back(
                std::move(candidate)
            );

            index_.insert(
                candidates_[slot].key,
                slot
            );

            const std::size_t position =
                heap_.size();

            heap_.push_back(slot);
            heap_position_.push_back(position);
            sift_up(position);

            result.status = PushStatus::Inserted;
            return result;
        }

        // ヒープの根は、現在保持している中で最悪の候補。
        const std::uint32_t worst_slot =
            heap_.front();

        if (
            !better(
                candidate,
                candidates_[worst_slot]
            )
        ) {
            return result;
        }

        result.status =
            PushStatus::ReplacedWorst;

        result.removed.emplace(
            std::move(candidates_[worst_slot])
        );

        index_.erase(result.removed->key);

        candidates_[worst_slot] =
            std::move(candidate);

        index_.insert(
            candidates_[worst_slot].key,
            worst_slot
        );

        // 根の候補が良くなったので下方向へ修復する。
        sift_down(0);

        return result;
    }

    // 保持している候補を良い順で返し、
    // セレクタを空の状態に戻す。
    [[nodiscard]]
    std::vector<CandidateType> drain_sorted() {
        std::vector<CandidateType> result =
            std::move(candidates_);

        std::sort(
            result.begin(),
            result.end(),
            better
        );

        candidates_.clear();
        candidates_.reserve(width_);

        heap_.clear();
        heap_position_.clear();

        index_.clear();

        return result;
    }

private:
    // scoreが小さい方を良い候補とする。
    //
    // scoreが等しい場合もStateKeyで順序を決めることで、
    // 実行ごとの結果を安定させる。
    [[nodiscard]] static bool better(
        const CandidateType& lhs,
        const CandidateType& rhs
    ) {
        if (lhs.score != rhs.score) {
            return lhs.score < rhs.score;
        }

        if (lhs.key.high != rhs.key.high) {
            return lhs.key.high < rhs.key.high;
        }

        return lhs.key.low < rhs.key.low;
    }

    // lhsの候補がrhsより悪いかを判定する。
    [[nodiscard]] bool slot_is_worse(
        const std::uint32_t lhs,
        const std::uint32_t rhs
    ) const {
        return better(
            candidates_[rhs],
            candidates_[lhs]
        );
    }

    // ヒープ上の2要素を交換し、
    // 逆引き配列も同時に更新する。
    void swap_heap_positions(
        const std::size_t lhs,
        const std::size_t rhs
    ) {
        std::swap(heap_[lhs], heap_[rhs]);

        heap_position_[heap_[lhs]] = lhs;
        heap_position_[heap_[rhs]] = rhs;
    }

    // 新しく追加された悪い候補を上方向へ移動する。
    void sift_up(std::size_t position) {
        while (position > 0) {
            const std::size_t parent =
                (position - 1) / 2;

            if (
                !slot_is_worse(
                    heap_[position],
                    heap_[parent]
                )
            ) {
                break;
            }

            swap_heap_positions(
                position,
                parent
            );

            position = parent;
        }
    }

    // 良くなった候補を下方向へ移動する。
    void sift_down(std::size_t position) {
        while (true) {
            const std::size_t left =
                position * 2 + 1;

            if (left >= heap_.size()) {
                break;
            }

            const std::size_t right =
                left + 1;

            std::size_t worse_child = left;

            if (
                right < heap_.size()
                && slot_is_worse(
                    heap_[right],
                    heap_[left]
                )
            ) {
                worse_child = right;
            }

            if (
                !slot_is_worse(
                    heap_[worse_child],
                    heap_[position]
                )
            ) {
                break;
            }

            swap_heap_positions(
                position,
                worse_child
            );

            position = worse_child;
        }
    }

    // candidates_[slot]の評価値を変更した後、
    // ヒープ条件を復元する。
    void fix_heap(const std::uint32_t slot) {
        const std::size_t position =
            heap_position_[slot];

        if (position > 0) {
            const std::size_t parent =
                (position - 1) / 2;

            if (
                slot_is_worse(
                    slot,
                    heap_[parent]
                )
            ) {
                sift_up(position);
                return;
            }
        }

        sift_down(position);
    }

    std::size_t width_ = 0;

    FlatIndexMap index_;

    std::vector<CandidateType> candidates_;

    // heap_[i]はcandidates_の添字。
    std::vector<std::uint32_t> heap_;

    // heap_position_[slot]はheap_上の位置。
    std::vector<std::size_t> heap_position_;
};
// 最初の状態を親として表す特殊な番号。
inline constexpr std::uint32_t ROOT_PARENT =
    std::numeric_limits<std::uint32_t>::max();

// 固定1手コスト版ビームサーチの設定。
struct FixedBeamConfig {
    std::size_t beam_width = 1;
    int max_turn = 1;

    // オイラーツアー配列の予約サイズ。
    // 0ならbeam_widthから自動計算する。
    std::size_t tour_reserve = 0;
};

// TopKSelectorのCandidateに格納する問題固有情報。
template <class Action, class Evaluation>
struct FixedBeamPayload {
    // 親状態から行った操作。
    Action action{};

    // 操作後の評価情報。
    Evaluation evaluation{};

    // 親となった葉の番号。
    std::uint32_t parent = ROOT_PARENT;
};

// ビームサーチの結果。
template <class Action>
struct FixedBeamResult {
    std::vector<Action> actions;

    std::int64_t score =
        std::numeric_limits<std::int64_t>::max();

    // 完成状態に到達したならtrue。
    // 最大ターンまでで最良の未完成状態を返した場合はfalse。
    bool finished = false;
};

// 選択された探索木をオイラーツアー形式で管理する。
//
// Stateには以下の型と関数が必要。
//
// using Action = ...;
// using Evaluation = ...;
//
// pair<Evaluation, StateKey> initial_node() const;
// int64_t score(const Evaluation&) const;
//
// template<class Emit>
// void expand(
//     const Evaluation&,
//     StateKey,
//     Emit&&
// );
//
// void apply(const Action&);
// void undo(const Action&);
template <class State>
class FixedBeamTree {
public:
    using Action = typename State::Action;
    using Evaluation = typename State::Evaluation;

    using Payload =
        FixedBeamPayload<Action, Evaluation>;

    using CandidateType =
        Candidate<Payload>;

    explicit FixedBeamTree(
        State initial_state,
        const std::size_t beam_width,
        const std::size_t tour_reserve
    )
        : state_(std::move(initial_state)),
          initial_node_(state_.initial_node()) {
        const std::size_t reserve_size =
            tour_reserve != 0
                ? tour_reserve
                : beam_width * 4 + 16;

        current_tour_.reserve(reserve_size);
        next_tour_.reserve(reserve_size);

        leaves_.reserve(beam_width);
        next_leaves_.reserve(beam_width);

        first_child_.reserve(beam_width);
        next_candidate_.reserve(beam_width);

        fixed_prefix_.reserve(256);
    }

    // 現在の全ての葉を訪問する。
    //
    // state_をオイラーツアーに沿ってapply/undoするため、
    // 各葉へ盤面をコピーする必要がない。
    //
    // visitorには次の4引数を渡す。
    //
    // State&          現在の葉の状態
    // Evaluation&     葉に保存された評価情報
    // StateKey        葉の状態キー
    // uint32_t        葉番号
    template <class Visitor>
    void for_each_leaf(Visitor&& visitor) {
        // まだ木が作られていない最初のターン。
        if (current_tour_.empty()) {
            visitor(
                state_,
                initial_node_.first,
                initial_node_.second,
                ROOT_PARENT
            );
            return;
        }

        for (const TourEntry& entry : current_tour_) {
            if (entry.kind == FORWARD) {
                // 共有されている内部辺を下る。
                state_.apply(entry.action);
            } else if (entry.kind == BACKWARD) {
                // 内部辺を戻る。
                state_.undo(entry.action);
            } else {
                // 葉へ一時的に進み、展開後にすぐ戻る。
                assert(entry.kind >= 0);

                const std::size_t leaf_index =
                    static_cast<std::size_t>(
                        entry.kind
                    );

                assert(leaf_index < leaves_.size());

                state_.apply(entry.action);

                visitor(
                    state_,
                    leaves_[leaf_index].evaluation,
                    leaves_[leaf_index].key,
                    static_cast<std::uint32_t>(
                        leaf_index
                    )
                );

                state_.undo(entry.action);
            }
        }
    }

    // TopKSelectorによって選択された候補だけを残し、
    // 探索木を次の深さへ進める。
    void update(
        const std::vector<CandidateType>& candidates
    ) {
        assert(!candidates.empty());

        next_tour_.clear();
        next_leaves_.clear();

        // 最初のターンでは全候補が根の直接の子になる。
        if (current_tour_.empty()) {
            for (
                const CandidateType& candidate :
                candidates
            ) {
                assert(
                    candidate.payload.parent
                    == ROOT_PARENT
                );

                append_new_leaf(candidate);
            }

            current_tour_.swap(next_tour_);
            leaves_.swap(next_leaves_);
            return;
        }

        // parentごとに候補をまとめる。
        //
        // vector<vector<Candidate>>にすると葉ごとに動的確保が
        // 発生するため、配列による単方向リストを構築する。
        first_child_.assign(
            leaves_.size(),
            NO_CANDIDATE
        );

        next_candidate_.assign(
            candidates.size(),
            NO_CANDIDATE
        );

        // 逆順に挿入し、元の候補順を維持する。
        for (
            std::size_t i = candidates.size();
            i-- > 0;
        ) {
            const std::uint32_t parent =
                candidates[i].payload.parent;

            assert(parent < leaves_.size());

            next_candidate_[i] =
                first_child_[parent];

            first_child_[parent] =
                static_cast<std::int32_t>(i);
        }

        // 古いツアーを走査し、子を持つ葉だけを残す。
        for (
            const TourEntry& entry :
            current_tour_
        ) {
            if (entry.kind >= 0) {
                const std::size_t leaf_index =
                    static_cast<std::size_t>(
                        entry.kind
                    );

                std::int32_t candidate_index =
                    first_child_[leaf_index];

                // この葉から候補が1つも選択されなかった。
                if (
                    candidate_index
                    == NO_CANDIDATE
                ) {
                    continue;
                }

                // 古い葉への辺を内部辺に変更する。
                next_tour_.push_back(
                    TourEntry{
                        FORWARD,
                        entry.edge_id,
                        entry.action,
                    }
                );

                // 選択された子を新しい葉として追加する。
                while (
                    candidate_index
                    != NO_CANDIDATE
                ) {
                    append_new_leaf(
                        candidates[
                            static_cast<std::size_t>(
                                candidate_index
                            )
                        ]
                    );

                    candidate_index =
                        next_candidate_[
                            static_cast<std::size_t>(
                                candidate_index
                            )
                        ];
                }

                next_tour_.push_back(
                    TourEntry{
                        BACKWARD,
                        entry.edge_id,
                        entry.action,
                    }
                );
            } else if (entry.kind == FORWARD) {
                // 既存の内部辺。
                next_tour_.push_back(entry);
            } else {
                assert(entry.kind == BACKWARD);
                assert(!next_tour_.empty());

                // FORWARD直後にBACKWARDが来るなら、
                // その部分木から葉が全て消えたことを表す。
                if (
                    next_tour_.back().kind
                    == FORWARD
                ) {
                    assert(
                        next_tour_.back().edge_id
                        == entry.edge_id
                    );

                    next_tour_.pop_back();
                } else {
                    next_tour_.push_back(entry);
                }
            }
        }

        current_tour_.swap(next_tour_);
        leaves_.swap(next_leaves_);

        compress_common_prefix();
    }

    // 根から指定した親葉までの操作列を復元する。
    [[nodiscard]]
    std::vector<Action> path_to_parent(
        const std::uint32_t parent
    ) const {
        std::vector<Action> path =
            fixed_prefix_;

        // 初期状態を親とする候補。
        if (parent == ROOT_PARENT) {
            return path;
        }

        assert(parent < leaves_.size());

        for (
            const TourEntry& entry :
            current_tour_
        ) {
            if (entry.kind == FORWARD) {
                path.push_back(entry.action);
            } else if (entry.kind == BACKWARD) {
                assert(!path.empty());
                path.pop_back();
            } else if (
                static_cast<std::uint32_t>(
                    entry.kind
                ) == parent
            ) {
                path.push_back(entry.action);
                return path;
            }
        }

        assert(false);
        return {};
    }

    // 親までの経路に候補自身の操作を加える。
    [[nodiscard]]
    std::vector<Action> path_to_candidate(
        const CandidateType& candidate
    ) const {
        std::vector<Action> path =
            path_to_parent(
                candidate.payload.parent
            );

        path.push_back(
            candidate.payload.action
        );

        return path;
    }

private:
    // TourEntry::kindの特殊値。
    static constexpr std::int32_t FORWARD = -1;
    static constexpr std::int32_t BACKWARD = -2;

    static constexpr std::int32_t NO_CANDIDATE =
        -1;

    // オイラーツアーの1要素。
    //
    // kind >= 0:
    //     kindは葉番号。actionで葉へ進んで戻る。
    //
    // kind == FORWARD:
    //     actionを適用して内部辺を進む。
    //
    // kind == BACKWARD:
    //     actionをundoして内部辺を戻る。
    struct TourEntry {
        std::int32_t kind = 0;

        // 同じ辺のFORWARD/BACKWARDを識別する番号。
        std::uint32_t edge_id = 0;

        Action action{};
    };

    // 各葉にだけ保存する情報。
    //
    // 盤面本体は保存しない。
    struct LeafData {
        Evaluation evaluation{};
        StateKey key{};
    };

    // candidateを次のツアーの葉として追加する。
    void append_new_leaf(
        const CandidateType& candidate
    ) {
        const std::int32_t leaf_index =
            static_cast<std::int32_t>(
                next_leaves_.size()
            );

        next_tour_.push_back(
            TourEntry{
                leaf_index,
                next_edge_id_++,
                candidate.payload.action,
            }
        );

        next_leaves_.push_back(
            LeafData{
                candidate.payload.evaluation,
                candidate.key,
            }
        );
    }

    // 全ての葉に共通する一本道を探索木の根へ取り込む。
    //
    // 例えば全候補が
    //
    // A -> B -> ...
    //
    // を共有しているなら、AやBを各ターンで何度も
    // apply/undoする必要はない。
    void compress_common_prefix() {
        std::size_t left = 0;
        std::size_t right =
            current_tour_.size();

        while (
            right - left >= 2
            && current_tour_[left].kind
                == FORWARD
            && current_tour_[right - 1].kind
                == BACKWARD
            && current_tour_[left].edge_id
                == current_tour_[right - 1].edge_id
        ) {
            state_.apply(
                current_tour_[left].action
            );

            fixed_prefix_.push_back(
                current_tour_[left].action
            );

            ++left;
            --right;
        }

        if (left == 0) {
            return;
        }

        const std::size_t new_size =
            right - left;

        // 新しいvectorを確保せず、残る区間を前へ移動する。
        for (
            std::size_t i = 0;
            i < new_size;
            ++i
        ) {
            current_tour_[i] =
                std::move(
                    current_tour_[left + i]
                );
        }

        current_tour_.resize(new_size);
    }

    // 現在の共通祖先の状態を保持する。
    State state_;

    // 初期状態の評価値とキー。
    std::pair<Evaluation, StateKey>
        initial_node_;

    std::vector<TourEntry> current_tour_;
    std::vector<TourEntry> next_tour_;

    std::vector<LeafData> leaves_;
    std::vector<LeafData> next_leaves_;

    // parentごとの候補リスト。
    std::vector<std::int32_t> first_child_;
    std::vector<std::int32_t> next_candidate_;

    // 全ての葉に共通し、探索木から切り離した経路。
    std::vector<Action> fixed_prefix_;

    std::uint32_t next_edge_id_ = 1;
};

// Candidate同士の共通比較関数。
// scoreが小さい方を良い候補とする。
template <class Payload>
[[nodiscard]]
bool fixed_candidate_better(
    const Candidate<Payload>& lhs,
    const Candidate<Payload>& rhs
) {
    if (lhs.score != rhs.score) {
        return lhs.score < rhs.score;
    }

    if (lhs.key.high != rhs.key.high) {
        return lhs.key.high < rhs.key.high;
    }

    return lhs.key.low < rhs.key.low;
}

// 固定1手コストのビームサーチ本体。
template <class State>
[[nodiscard]]
FixedBeamResult<typename State::Action>
fixed_beam_search(
    State initial_state,
    const FixedBeamConfig& config
) {
    using Tree = FixedBeamTree<State>;
    using Action = typename Tree::Action;
    using Evaluation = typename Tree::Evaluation;
    using Payload = typename Tree::Payload;
    using CandidateType =
        typename Tree::CandidateType;

    assert(config.beam_width > 0);
    assert(config.max_turn > 0);

    Tree tree(
        std::move(initial_state),
        config.beam_width,
        config.tour_reserve
    );

    TopKSelector<Payload> selector(
        config.beam_width
    );

    for (
        int turn = 0;
        turn < config.max_turn;
        ++turn
    ) {
        std::optional<CandidateType>
            best_finished;

        // 全ての葉をapply/undoで巡回する。
        tree.for_each_leaf(
            [&](
                State& state,
                const Evaluation& evaluation,
                const StateKey key,
                const std::uint32_t parent
            ) {
                // State::expandは候補ごとにemitを呼ぶ。
                state.expand(
                    evaluation,
                    key,
                    [&](
                        Action action,
                        Evaluation next_evaluation,
                        const StateKey next_key,
                        const bool finished
                    ) {
                        CandidateType candidate{
                            next_key,
                            state.score(
                                next_evaluation
                            ),
                            Payload{
                                std::move(action),
                                std::move(
                                    next_evaluation
                                ),
                                parent,
                            },
                        };

                        // 固定1手コストなので、最初に完成候補が
                        // 発生した深さが最短ターンになる。
                        if (finished) {
                            if (
                                !best_finished
                                    .has_value()
                                || fixed_candidate_better(
                                    candidate,
                                    *best_finished
                                )
                            ) {
                                best_finished =
                                    std::move(
                                        candidate
                                    );
                            }

                            return;
                        }

                        [[maybe_unused]]
                        const auto push_result =
                            selector.push(
                                std::move(
                                    candidate
                                )
                            );
                    }
                );
            }
        );

        if (best_finished.has_value()) {
            return FixedBeamResult<Action>{
                tree.path_to_candidate(
                    *best_finished
                ),
                best_finished->score,
                true,
            };
        }

        std::vector<CandidateType> selected =
            selector.drain_sorted();

        // どの状態からも遷移できなかった。
        if (selected.empty()) {
            return {};
        }

        // 最大ターンに到達した場合は、
        // 完成していなくても最良状態を返す。
        if (turn + 1 == config.max_turn) {
            return FixedBeamResult<Action>{
                tree.path_to_candidate(
                    selected.front()
                ),
                selected.front().score,
                false,
            };
        }

        tree.update(selected);
    }

    return {};
}
} // namespace fast_beam
