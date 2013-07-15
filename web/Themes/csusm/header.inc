<?php

// $Id: header.inc 2561 2012-11-06 19:06:15Z cimorrison $


// Print the page header
function print_theme_header($day, $month, $year, $area, $room)
{
  global $mrbs_company, $mrbs_company_logo, $mrbs_company_url, $mrbs_company_more_info,
         $search_str, $locale_warning;
  global $tbl_entry, $tbl_room, $tbl_area;
  global $PHP_SELF, $HTTP_HOST, $QUERY_STRING;
  global $view_week_number, $weekstarts, $times_along_top, $periods, $enable_periods;
  global $auth, $max_level;
  global $default_language_tokens, $disable_automatic_language_changing, $override_locale;
  global $select_options;
  global $ajax_refresh_rate;
  global $main_table_cell_border_width, $main_cell_height;
  global $timetohighlight;

  $page = basename($PHP_SELF, ".php");
  $user = getUserName();
  $is_admin = (authGetUserLevel($user) >= $max_level);
  if(authGetUserLevel($user)> 0){
    $loggedin=" loggedin-user";
  } else{
    $loggedin = " guest-user";
  }
  // Need to set the timezone before we can use date()
  get_area_settings($area);

  // If we dont know the right date then make it up
  if (!$day)
  {
    $day   = date("d");
  }
  if (!$month)
  {
    $month = date("m");
  }
  if (!$year)
  {
    $year  = date("Y");
  }
  if (!isset($search_str))
  {
    $search_str = "";
  }

  http_headers();
  echo DOCTYPE;
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="<?php echo get_charset(); ?>">
    <title><?php echo get_vocab("mrbs") ?></title>
    <?php
    require_once "style.inc";
    ?>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="//netdna.bootstrapcdn.com/twitter-bootstrap/2.3.2/css/bootstrap-combined.no-icons.min.css" rel="stylesheet">
    <link href="//netdna.bootstrapcdn.com/font-awesome/3.2.1/css/font-awesome.min.css" rel="stylesheet">
    <link href='//fonts.googleapis.com/css?family=Source+Sans+Pro:400,900|Courgette' rel='stylesheet' type='text/css'>
    <link rel="stylesheet" type="text/css" href="/scheduler/Themes/csusm/styles/local.css">
    <script type="text/javascript" src="//cdnjs.cloudflare.com/ajax/libs/modernizr/2.6.2/modernizr.min.js"></script>
    <?php
    require_once "js.inc";
    ?>
    <script type="text/javascript">
      $(document).ready(function() {
        $('.dwm_main').addClass('table table-bordered');
        $('.trailer').first().attr('id','simple_trailer_header');
        $('#simple_trailer_header #simple').attr('id','simple_header');
        $('#simple_header a').addClass('btn btn-info');
        $("#simple_trailer_header").appendTo("#overview");
        $('input[type=submit]').addClass('btn');
        $('#logon_box input[type=submit]').addClass('btn-primary');
        $('#edit_entry_submit_save input[type=submit]').addClass('btn-primary');
        $('form#logon').addClass('well');
        $('form.form_general').addClass('well');
        $('#dwm_header ul').addClass('nav nav-pills');
        $('#dwm_header .current').parents('li').addClass('active');
        $('#area_form form').addClass('well form-inline');
        $('#areaChangeForm input.button').addClass('btn');
        $('#areaChangeForm input[type=edit]').addClass('btn btn-info');
        $('#areaChangeForm input[type=delete]').addClass('btn btn-danger');
        $('#edit_room').addClass('well');
        $('#cals').before('<div id="cal-handle" class="btn btn-info"><i class="icon-circle-arrow-down icon-white"></i> View MiniCal</div>');
        $('#company #Form1').delay(1000).fadeIn(1000);
        $('.dropdown-toggle').dropdown();
        $("#cal-handle").appendTo("#simple_trailer_header");
        $("#cal-handle").click(function(){
          if($("#cals").hasClass('open')){
            $("#cals").slideUp(150).removeClass('open');
            $("#cal-handle i").removeClass('icon-circle-arrow-up');
            $("#cal-handle i").addClass('icon-circle-arrow-down');
          } else {
            $("#cals").slideDown(150).addClass('open');
            $("#cal-handle i").removeClass('icon-circle-arrow-down');
            $("#cal-handle i").addClass('icon-circle-arrow-up');
          }
        });
      });
    </script>
    <script src="//netdna.bootstrapcdn.com/twitter-bootstrap/2.3.2/js/bootstrap.min.js"></script>
    <script type="text/javascript">
      var _gaq = _gaq || [];
      _gaq.push(['_setAccount', 'UA-4199304-3']);
      _gaq.push(['_trackPageview']);

      (function() {
        var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
        ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
        var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
      })();
    </script>
  </head>
  <?php
  // Put the filename in as a class to aid styling.
  // (Use a class rather than id to avoid specificity problems)
  echo "<body class=\"non_js ".htmlspecialchars($page). $loggedin ."\">\n";
  // Add a class of "js" so that we know if we're using JavaScript or not
  // and remove the non_js class (it's sometimes useful to know that we're
  // not running JavaScript)
  ?>
  <script type="text/javascript">
    //<![CDATA[
    $('body').addClass('js').removeClass('non_js');
    //]]>
  </script>
  <div class="screenonly">
    <?php // show a warning if this is using a low version of php
      if (substr(phpversion(), 0, 1) == 3){
        echo "<h1>" . get_vocab("not_php3") . "</h1>\n";
      }
      if (!empty($locale_warning)){
        echo "[Warning: ".$locale_warning."]";
      }
    ?>
  <div id="banner" class="navbar">
    <div id="company" class="navbar-inner">
      <div class="container">
        <ul class="nav">
          <?php
          echo "<li class=\"divider-vertical\"></li>";
          echo "<li><a href=\"index.php\"><i class=\"icon-home icon-white\"></i> Home</a></li>";
          echo "<li class=\"divider-vertical\"></li>";
          ?>
        </ul>
        <form action="day.php" method="get" id="Form1" class="navbar-search pull-left">
          <div><i class="icon-calendar icon-white"></i>
            <?php
            // Give the form id as the optional fifth parameter because we want
            // the form to be automatically submitted when the datepicker is closed
            genDateSelector("", $day, $month, $year, "Form1");
            if (!empty($area)){
              echo "<input type=\"hidden\" name=\"area\" value=\"$area\">\n";
            }
            if (!empty($room)){
              echo "<input type=\"hidden\" name=\"room\" value=\"$room\">\n";
            }
            // Although the datepicker will automatically go to the new date when
            // the date is changed, we still need a submit button because there
            // are occasions when you want to go to the date without changing it -
            // for example when you've been on a Search or Report page
            echo "<input type=\"submit\" value=\"" . get_vocab("goto") . "\" class=\"btn\"/>\n";
            ?>
           </div>
        </form>
        <ul class="nav"><li class="divider-vertical"></li></ul>
          <?php
          // For session protocols that define their own logon box...
          if (function_exists('PrintLogonBox')){
            echo "<div id=\"logon_box\"><i class=\"icon-user icon-white\"></i>\n";
            PrintLogonBox();
            echo "</div>\n";
          }?>
        <ul class="nav">
          <?php
            // Provide a link to the list of bookings awaiting approval
            // (if there are any enabled areas where we require bookings to be approved)

          $approval_somewhere = some_area('approval_enabled', TRUE);
          if ($approval_somewhere && (authGetUserLevel($user) >= 1)){
            $sql_approval_enabled = some_area_predicate('approval_enabled');
            // Find out how many bookings are awaiting approval
            // (but only for areas where approval is required)
            $sql = "SELECT COUNT(*)
                      FROM $tbl_entry E, $tbl_room R, $tbl_area A
                     WHERE (status&" . STATUS_AWAITING_APPROVAL . " != 0)
                       AND E.room_id = R.id
                       AND R.area_id = A.id
                       AND R.disabled = 0
                       AND A.disabled = 0
                       AND $sql_approval_enabled";
            if (!$is_admin){
              // Ordinary users can only see their own
              $sql .= " AND create_by='" . sql_escape($user) . "'";
            }
            $n_outstanding = sql_query1($sql);
            if ($n_outstanding < 0){
              trigger_error(sql_error(), E_USER_WARNING);
              fatal_error(FALSE, get_vocab("fatal_db_error"));
            }
            echo "<div id=\"n_outstanding\"" .
                 (($n_outstanding > 0) ? " class=\"outstanding\"" : '') .
                 ">\n";
            echo "<a href=\"pending.php?day=$day&amp;month=$month&amp;year=$year&amp;area=$area" .
                 ((!empty($room)) ? "&amp;room=$room" : "") .
                 "\"><i class=\"icon-inbox icon-white\"></i> $n_outstanding " . get_vocab("outstanding") . "</a>\n";
            echo "</div>\n";
          }

        $query_str = "day=$day&amp;month=$month&amp;year=$year";
        if (!empty($area)){
          $query_str .= "&amp;area=$area";
        }
        if (!empty($room)){
          $query_str .= "&amp;room=$room";
        }
        echo "<li id=\"need-help\"><a href=\"/external/contact-library/email-us?area=libcirc@csusm.edu\"><i class=\"icon-question-sign icon-white\"></i> Need Help?</a></li>";
        echo "<li id=\"room-use-info\">\n";
        echo "<a href=\"http://biblio.csusm.edu/external/group-study-rooms/group-study-rooms\"><i class=\"icon-info-sign icon-white\"></i> Room Use Info</a>\n";
        echo "</li>\n";
        echo "<li class=\"divider-vertical\"></li>";
        echo "<li id=\"admin\">\n";
        echo "<a href=\"admin.php?$query_str\"><i class=\"icon-cog icon-white\"></i> " . get_vocab("rooms") . "</a>\n";
        echo "</li>\n";
        echo "<li class=\"divider-vertical\"></li>";
        echo "<li id=\"issues\">\n";
        echo "<a href=\"https://lib.csusm.edu/base/projects/project0142/issues/new\"><i class=\"icon-exclamation-sign icon-white\"></i> Report a Problem</a>\n";
        echo "</li>\n";
        echo "<li class=\"divider-vertical\"></li>";
        if (authGetUserLevel($user) > 1){
          echo "<li id=\"report\">\n";
          echo "<a href=\"report.php?$query_str\"><i class=\"icon-list-alt icon-white\"></i> " . get_vocab("report") . "</a>\n";
          echo "</li>\n";
          echo "<li class=\"divider-vertical\"></li>";
        }
        ?>
        <li class="dropdown">
            <a href="#" class="dropdown-toggle" data-toggle="dropdown">
            CSUSM Library<b class="caret"></b></a>
            <ul class="dropdown-menu">
              <li><a href="http://biblio.csusm.edu">Home</a></li>
              <li><a href="http://biblio.csusm.edu/hours_calendar">Hours</a></li>
              <li><a href="http://biblio.csusm.edu/ask-us">Ask Us!</a></li>
              <li><a href="http://biblio.csusm.edu/research_portal/databases">Databases</a></li>
              <li><a href="http://library.csusm.edu/catalog/">Books, Media, &amp; More</a></li>
              <li class="divider"></li>
              <li class="nav-header">CSUSM</li>
              <li><a href="http://www.csusm.edu">Home</a></li>
              <li><a href="https://my.csusm.edu">MyCSUSM</a></li>
              <li><a href="http://www.csusm.edu/iits/support/password/index.html">Password FAQs</a></li>
            </ul>
          </li>
      </ul>
      <?php
      if (authGetUserLevel($user) > 1){
      ?>
        <form id="header_search" method="get" action="search.php" class="navbar-search pull-right">
          <div><i class="icon-search icon-white"></i>
            <input type="search" name="search_str" value="<?php echo htmlspecialchars($search_str) ?>" class="search-query" placeholder="Search">
              <a href="search.php?advanced=1"><?php echo get_vocab("search") ?></a>
              <input type="hidden" name="day" value="<?php echo $day;?>">
              <input type="hidden" name="month" value="<?php echo $month;?>">
              <input type="hidden" name="year" value="<?php echo $year;?>">
              <?php
              if (!empty($area)){
                echo "<input type=\"hidden\" name=\"area\" value=\"$area\">\n";
              }
              if (!empty($room)){
                echo "<input type=\"hidden\" name=\"room\" value=\"$room\">\n";
              }
            ?>
          </div>
        </form>
      <?php
      }
      ?>
      </div>
    </div>
    <?php
    echo generate_trailer();
    ?>
  </div>
  <div id="contents">
  <header class="subhead" id="overview">
    <h1><?php
    echo "<a href=\"index.php\" class=\"brand\"> ";
    echo get_vocab("mrbs");
    echo "</a>";
    ?></h1>
  </header>
  <?php
  } // end of print_theme_header()
  ?>
