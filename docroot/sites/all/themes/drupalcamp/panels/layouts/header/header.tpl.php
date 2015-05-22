<?php
/**
 * @file
 * Template for the Mondrian layout.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>
<header class="header region-header">
    <div class="row header-row full clearfix">
        <div class="section-outer-wrapper">
            <div class="section-inner-wrapper">
                <a href="#" class="nav-button" id="touch-menu" data-icon="menu"></a>
                <?php if ($content['header_top']){ ?>
                <div class="row header-top full">
				    <?php print render($content['header_top']); ?>
				</div>  
                <?php } ?>
                <?php if ( theme_get_setting('logo')): ?>
                    <a href="/" title="<?php print t('Home'); ?>" rel="home" class="site-logo">
                     <img src="<?php print theme_get_setting('logo'); ?>" alt="<?php print t('Home'); ?>" />
                    </a>
                <?php endif; ?>
                <?php if ($content['header_bottom']){ ?>
	                <div class="row header-bottom">
					    <?php print render($content['header_bottom']); ?>
					</div>
                <?php } ?>
                <a href="#" data-icon="search" class="search-button">Search</a>
            </div>
        </div>
    </div>
</header>
