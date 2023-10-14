#ifndef IVL_blockdiag_priv_H
#define IVL_blockdiag_priv_H

# include <string>
# include  "ivl_target.h"


struct output_parameters {
  std::string filename;
  std::string type;
};

extern output_parameters output_param;

extern int scan_scope(ivl_scope_t scope);

output_parameters get_output_parameters(ivl_design_t des) {
  // note to self: ivl_design_flag returns empty string "" if flag is not found
  output_param.filename.assign(ivl_design_flag(des, "-o"));
  output_param.type.assign(ivl_design_flag(des, "block_type"));
  return output_param;
};

#endif /* IVL_blockdiag_priv_H */
