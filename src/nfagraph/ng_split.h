/*
 * Copyright (c) 2015-2016, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of Intel Corporation nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \file
 * \brief Functions for splitting NFAGraphs into LHS and RHS.
 */

#ifndef NG_SPLIT_H
#define NG_SPLIT_H

#include <vector>

#include "ng_holder.h"
#include "util/ue2_containers.h"

namespace ue2 {

class NGHolder;

/** Note: pivot should be a vertex that dominates acceptEod. Treating 'in'
 * allocated to rhs if they are reachable from the pivot. Conversely, a vertex
 * is in the lhs if it is reachable from start without going through the
 * pivot. The pivot ends up in the LHS and any adjacent vertices in the RHS.
 *
 * Note: The RHS is setup to be triggered by TOP 0
 *
 * When multiple split vertices are provided:
 * - RHS contains all vertices reachable from every pivot
 * - LHS contains all vertices which are reachable from start ignoring any
 *   vertices which have an edge to every pivot
 */
void splitGraph(const NGHolder &base, NFAVertex pivot, NGHolder *lhs,
                ue2::unordered_map<NFAVertex, NFAVertex> *lhs_map,
                NGHolder *rhs,
                ue2::unordered_map<NFAVertex, NFAVertex> *rhs_map);

void splitGraph(const NGHolder &base, const std::vector<NFAVertex> &pivots,
                NGHolder *lhs,
                ue2::unordered_map<NFAVertex, NFAVertex> *lhs_map,
                NGHolder *rhs,
                ue2::unordered_map<NFAVertex, NFAVertex> *rhs_map);

void splitLHS(const NGHolder &base, NFAVertex pivot, NGHolder *lhs,
              ue2::unordered_map<NFAVertex, NFAVertex> *lhs_map);

void splitRHS(const NGHolder &base, const std::vector<NFAVertex> &pivots,
              NGHolder *rhs, ue2::unordered_map<NFAVertex, NFAVertex> *rhs_map);

} // namespace ue2

#endif // NG_SPLIT_H
