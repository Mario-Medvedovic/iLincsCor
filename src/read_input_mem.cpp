#include "ilincs_corx.h"
#include "util.h"

/*
 * Read tsv input file and for a given library format the vector of value, weight and whether the gene is included
 * also return the number of gene ids found
 */
int read_input_mem(std::vector<int> gene_ids,
               std::vector<int> *input_gene_ids, std::vector<double> *input_data, std::vector<double> *input_pvalues,
               t_input *input, t_input *input_weights, t_input_included *input_included, int *found_geneids,
               t_input *input_src, t_input *input_weights_src, t_input_map *input_map)
{
   *found_geneids=0;

   int n = input_gene_ids->size();
   if (n == 0) return -1;

   // read input vector and assign logdiffexp to appropriate geneids positions
   std::fill((*input).begin(), (*input).end(), 0);
   std::fill((*input_weights).begin(), (*input_weights).end(), 0);
   std::fill((*input_included).begin(), (*input_included).end(), 0);
   int n_rows = input->size();
   for(int i = 1; i < n && i <= n_rows; i++){
      // DEBUG(cerr << "Converting " << input_vec_vec[i][LogDiffExp_column] << " at line " << i << " column " << LogDiffExp_column << endl;)

      int gene_position=i-1;

      PRECISION input_exp = (*input_data)[i-1];
      PRECISION input_pvalue = (*input_pvalues)[i-1];
      input_pvalue = -1*log10(input_pvalue);
      int gene_id = (*input_gene_ids)[i-1];
      // shortcut
      if (gene_id != gene_ids[gene_position]) {

            // FIXME: make this binary search
            std::vector<int>::iterator it = std::find(gene_ids.begin(), gene_ids.end(), gene_id);
            if (it == gene_ids.end()) {
               gene_position = -1; // can't find gene_id
            } else {
               gene_position = std::distance(gene_ids.begin(), it);
            }
      }
      if ((*input_included)[gene_position]==0) {
            (*found_geneids)++;
      }
      (*input)[gene_position]=input_exp;
      (*input_weights)[gene_position]=input_pvalue;
      (*input_included)[gene_position]=1;

	  // map
	  if (input_src) input_src->push_back(input_exp);
	  if (input_weights_src) input_weights_src->push_back(input_pvalue);
	  if (input_map) input_map->push_back(gene_position);
   }
   return 0;
}
