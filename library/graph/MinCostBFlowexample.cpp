#include "min_cost_bflow.hpp"
using FLOW = long long;
using COST = long long;

mincost_bflow::MinCostBFlow<FLOW, COST> m(V);
m.add_edge(u, v, lower, upper, cost);
m.add_ds(v, supply_minus_demand); // 供給>0, 需要<0
auto [ok, min_cost] = m.solve();
