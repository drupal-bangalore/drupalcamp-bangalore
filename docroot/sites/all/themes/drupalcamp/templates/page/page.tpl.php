<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $secondary_menu_heading: The title of the menu used by the secondary links.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['branding']: Items for the branding region.
 * - $page['header']: Items for the header region.
 * - $page['touch_header']: Items for the touch header region.
 * - $page['navigation']: Items for the navigation region.
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see omega_preprocess_page()
 */
?>

<div class="snap-content content-outer-wrapper page layout" id="content">
  <?php print render($title_suffix); ?>
    <header class="header region-header">
        <div class="row header-row full clearfix">
            <div class="section-outer-wrapper">
                <div class="section-inner-wrapper">
                    <a href="#" class="nav-button" id="touch-menu" data-icon="menu"></a>
                    <?php if (isset($page['header_top'])) { ?>
                            <?php print render($page['header_top']); ?>
                    <?php } ?>
                    <?php if ($logo) : ?>
                        <a href="/" title="<?php print t('Home'); ?>" rel="home" class="site-logo">
                         <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                        </a>
                    <?php endif; ?>
                    <?php if (isset($page['header_bottom'])) { ?>
                      <div class="social-links">
                        <?php print render($page['header_bottom']); ?>
                      </div>
                    <?php } ?>
                    <?php if ($page['highlighted']) { ?>
                        <div class="row highlighted-row">
                            <?php print render($page['highlighted']); ?>
                        </div>
                    <?php } ?>
                    <!--<a href="#" data-icon="search" class="search-button">Search</a>-->
                </div>
            </div>
        </div>
    </header>

    <?php if (isset($page['navigation'])) { ?>
    <div class="row navigation-row hidden">
        <?php print render($page['navigation']); ?>
    </div>
    <?php } ?>

    <?php if (!$is_front) :
			if($breadcrumb): ?>
        <div class="row breadcrumb-row">
            <div class="section-outer-wrapper full">
                <div class="section-inner-wrapper">
                    <?php print str_replace('®', '<sup>®</sup>', $breadcrumb); ?>
                </div>
            </div>
        </div>
    <?php endif;
		endif; ?>
    
    <?php if (isset($page['social_share'])) { ?>
        <div class="row siteshare-row">
          <div class="section-outer-wrapper full">
            <div class="section-inner-wrapper">
              <?php print render($page['social_share']); ?>
            </div>
          </div>
        </div>
    <?php } ?>

    <?php if (!empty($tabs)) { ?>
        <div class="row tabs-row">
            <div class="section-outer-wrapper full">
                <div class="section-inner-wrapper">
                    <?php print render($tabs); ?>
                </div>
            </div>
        </div>
    <?php } ?>

    <?php if ($messages){ ?>
        <div class="row messages-row">
            <div class="section-outer-wrapper full">
                <div class="section-inner-wrapper">
                    <?php print render($messages); ?>
                </div>
            </div>
        </div>
    <?php } ?>

    <?php if ($action_links){ ?>
        <div class="row action_links-row">
            <div class="section-outer-wrapper full">
                <div class="section-inner-wrapper">
                    <ul class="action-links"><?php print render($action_links); ?></ul>
                </div>
            </div>
        </div>
    <?php } ?>

    <?php if ($page['help']){ ?>
        <div class="row help-row">
            <?php print render($page['help']); ?>
        </div>
    <?php } ?>

    <?php if ($page['sidebar_first']){ ?>
        <div class="row left-content-row">
          <div class="section-inner-wrapper clearfix">
            <?php print render($page['sidebar_first']); ?>
          </div>
        </div>
    <?php } ?>
    
    
    <?php if ($page['content']){ ?>
        <div class="row content-row">
            <div class="section-outer-wrapper">
                <div class="section-inner-wrapper clearfix">
                    <?php
                      $pane_title_override = isset($pane_title_override) ? $pane_title_override : false;
                      if (!empty($title) && !$is_front && !$pane_title_override){ ?>
                      <h1><?php print $title; ?></h1>
                    <?php } ?>
                    <?php print render($page['content']); ?>
                </div>
            </div>
        </div>
    <?php } ?>
    
    <?php if ($page['sidebar_second']){ ?>
        <div class="row left-content-row">
          <div class="section-inner-wrapper clearfix">
            <?php print render($page['sidebar_second']); ?>
          </div>
        </div>
    <?php } ?>

    <div class="sticky-footer"></div>
</div>

<?php if ($page['footer']){ ?>
<div class="footer_wrapper">
    <footer class="row footer-row" id="footer" role="contentinfo">
        <!--<a href="#" class="top-link">Back to Top</a>-->
        <div class="section-outer-wrapper">
            <div class="section-inner-wrapper">
                <?php print render($page['footer']); ?>
            </div>
        </div>
    </footer>
</div>
<?php } ?>
