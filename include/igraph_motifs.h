/* -*- mode: C -*-  */
/* 
   IGraph library.
   Copyright (C) 2009  Gabor Csardi <csardi@rmki.kfki.hu>
   MTA RMKI, Konkoly-Thege Miklos st. 29-33, Budapest 1121, Hungary
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,  51 Franklin Street, Fifth Floor, Boston, MA 
   02110-1301 USA

*/

#ifndef IGRAPH_MOTIFS_H
#define IGRAPH_MOTIFS_H

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

#include "igraph_types.h"
#include "igraph_datatype.h"

__BEGIN_DECLS

/* -------------------------------------------------- */
/* Graph motifs                                       */
/* -------------------------------------------------- */

/**
 * \typedef igraph_motifs_handler_t
 * Callback type for \c igraph_motifs_randesu_callback
 * 
 * \ref igraph_motifs_randesu_callback() calls a specified callback
 * function whenever a new motif is found during a motif search. This
 * callback function must be of type \c igraph_motifs_handler_t. It has
 * the following arguments:
 * \param graph The graph that that algorithm is working on. Of course
 *   this must not be modified.
 * \param vids The IDs of the vertices in the motif that has just been
 *   found. This vector is owned by the motif search algorithm, so do not
 *   modify or destroy it; make a copy of it if you need it later.
 * \param isoclass The isomorphism class of the motif that has just been
 *   found. Use \ref igraph_isoclass or \ref igraph_isoclass_subgraph to find
 *   out which isomorphism class belongs to a given motif.
 * \param extra The extra argument that was passed to \ref
 *   igraph_motifs_randesu_callback().
 * \return A logical value, if TRUE (=non-zero), that is interpreted
 *    as a request to stop the motif search and return to the caller.
 * 
 * \sa \ref igraph_motifs_randesu_callback()
 */

typedef igraph_bool_t igraph_motifs_handler_t(const igraph_t *graph,
					      igraph_vector_t *vids,
					      int isoclass,
					      void* extra);

int igraph_motifs_randesu(const igraph_t *graph, igraph_vector_t *hist, 
			  int size, const igraph_vector_t *cut_prob);

int igraph_motifs_randesu_callback(const igraph_t *graph, int size,
				   const igraph_vector_t *cut_prob,
				   igraph_motifs_handler_t *callback,
				   void* extra);

int igraph_motifs_randesu_estimate(const igraph_t *graph, igraph_integer_t *est,
				   int size, const igraph_vector_t *cut_prob, 
				   igraph_integer_t sample_size, 
				   const igraph_vector_t *sample);
int igraph_motifs_randesu_no(const igraph_t *graph, igraph_integer_t *no,
			     int size, const igraph_vector_t *cut_prob);

int igraph_dyad_census(const igraph_t *graph, igraph_integer_t *mut,
		       igraph_integer_t *asym, igraph_integer_t *null);
int igraph_triad_census(const igraph_t *igraph, igraph_vector_t *res);
int igraph_triad_census_24(const igraph_t *graph, igraph_integer_t *res2,
			   igraph_integer_t *res4);

__END_DECLS

#endif
