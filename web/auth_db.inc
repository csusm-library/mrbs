<?php
/*****************************************************************************
*
*   File name       auth_db.inc
*
*   Description     Authenticate users from a table in the MRBS database.
*
*   Notes           To use this authentication scheme, set in config.inc.php:
*         $auth["type"]  = "db";
*
*   History
*    Available in the source control system
*
******************************************************************************/

// $Id: auth_db.inc 2277 2012-03-26 09:25:53Z cimorrison $

/* session_php.inc and session_cookie.inc will add a link to the user list
    in the logon box, if the value $user_list_link is set. */
$user_list_link = "edit_users.php";


/* authValidateUser($user, $pass)
 * 
 * Checks if the specified username/password pair are valid
 * 
 * $user  - The user name
 * $pass  - The password
 * 
 * Returns:
 *   0        - The pair are invalid or do not exist
 *   non-zero - The pair are valid
 */

function authValidateUser($user, $pass)
{
  global $tbl_users;

  $user = strtolower(sql_escape($user));
  // No sql_escape() required because it's put in the database as an MD5,
  // which is safe.
  $pass = md5($pass);
  
  $result = sql_query1("SELECT COUNT(*) FROM $tbl_users WHERE name='$user' AND password='$pass' LIMIT 1");
  if ($result == -1)
  {
    trigger_error(sql_error(), E_USER_WARNING);
    return 0;
  }

  return $result;
}

/* authGetUserLevel($user)
 * 
 * Determines the user's access level
 * 
 * $user - The user name
 *
 * Returns:
 *   The users access level
 */
function authGetUserLevel($user)
{
  global $tbl_users;
  // User not logged in, user level '0'
  if(!isset($user))
  {
    return 0;
  }
  
  $result = sql_query1("SELECT level FROM $tbl_users WHERE name='" . strtolower(sql_escape($user)) . "' LIMIT 1");
  if ($result == -1)
  {
    $sql_error = sql_error();
    if (!empty($sql_error))
    {
      // It's possible that sql_query1 returned -1 because there were no matching rows,
      // so we only trigger an error if there was a genuine SQL error.
      trigger_error($sql_error, E_USER_WARNING);
    }
    return 0;
  }

  return $result;
}

?>