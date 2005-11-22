/*
 * ====================================================================
 * Copyright (c) 2002-2005 The RapidSvn Group.  All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library (in the file LGPL.txt); if not,
 * write to the Free Software Foundation, Inc., 51 Franklin St,
 * Fifth Floor, Boston, MA  02110-1301  USA
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */

// subversion api
#include "svn_wc.h"

// svncpp
#include "svncpp/exception.hpp"
#include "svncpp/path.hpp"
#include "svncpp/pool.hpp"
#include "svncpp/wc.hpp"


namespace svn
{
  const char * Wc::ADM_DIR_NAME = SVN_WC_ADM_DIR_NAME;

  bool
  Wc::checkWc (const char * dir)
  {
    Pool pool;
    Path path (dir);
    int wc;

    svn_error_t * error = svn_wc_check_wc (
#if QT_VERSION < 0x040000
        path.path().utf8(),
#else
        path.path().toUtf8(),
#endif
        &wc, pool);

    if ((error != NULL) || (wc == 0))
    {
      return false;
    }

    return true;
  }

  void
  Wc::ensureAdm (const char * dir, const char *uuid,
                 const char * url, const Revision & revision)
  {
    Pool pool;
    Path dirPath (dir);
    Path urlPath (url);

#if QT_VERSION < 0x040000
    svn_error_t * error =
      svn_wc_ensure_adm (
                         dirPath.path().utf8(),    // path
                         uuid,                // UUID
                         urlPath.path().utf8(),    // url
                         revision.revnum (),  // revision
                         pool);
#else
    svn_error_t * error =
      svn_wc_ensure_adm (
                         dirPath.path().toUtf8(),    // path
                         uuid,                // UUID
                         urlPath.path().toUtf8(),    // url
                         revision.revnum (),  // revision
                         pool);
#endif
    if(error != NULL)
      throw ClientException (error);
  }
}

/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../../rapidsvn-dev.el")
 * end:
 */
