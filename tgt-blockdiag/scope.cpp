/*
 * Copyright (c) 2023 Daniel Vicente Lühr Sierra (dvls@ieee.org)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "blockdiag_priv.h"
# include <map>
# include <string>
# include <cassert>
# include <cstdio>

using namespace std;


struct attr_value {
      ivl_attribute_type_t type;
      string str;
      long num;
};


static void draw_block(ivl_scope_t scope, const map<string,attr_value>&attrs);

int scan_scope(ivl_scope_t scope)
{
  // get attributes
  map<string,attr_value> attrs;
  // Scan the attributes

  for (unsigned idx = 0 ; idx < ivl_scope_attr_cnt(scope) ; idx += 1) {
    ivl_attribute_t attr = ivl_scope_attr_val(scope, idx);
    string attr_key = attr->key;
    struct attr_value val;
    val.type = attr->type;
    switch (val.type) {
    case IVL_ATT_VOID:
      break;
    case IVL_ATT_STR:
      val.str = attr->val.str;
      break;
    case IVL_ATT_NUM:
      val.num = attr->val.num;
      break;
    }
    attrs[attr_key] = val;
  }
  
  draw_block(scope, attrs);

  return 0;
  
}

extern "C" int child_scan_fun(ivl_scope_t scope, void*)
{
      scan_scope(scope);
      return 0;
}

/*
 * Draw a block diagram using the port info
 *
 */
static void draw_block(ivl_scope_t scope, const map<string,attr_value>&attrs)
{
  //assert(ivl_scope_type(scope) == IVL_SCT_MODULE);
  if (ivl_scope_type(scope) == IVL_SCT_MODULE)
    printf("   Component %s is %s\n", ivl_scope_name(scope), ivl_scope_tname(scope));
  
  ivl_scope_children(scope, child_scan_fun, 0);
}
