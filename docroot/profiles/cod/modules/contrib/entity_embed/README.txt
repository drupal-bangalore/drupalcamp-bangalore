CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Installation
 * Technical details

INTRODUCTION
------------

Current Maintainers:

 * Devin Carlson <http://drupal.org/user/290182>

Entity Embed integrates with CKEditor to allow any entity to be embedded within
a text area.

REQUIREMENTS
------------

Entity Embed requires Drupal 7.37 or later. It has five dependencies and needs
two libraries.

Drupal core modules
 * Filter

Contributed modules
 * Chaos Tools
 * CKEditor - The latest development release.
 * Entity
 * jQuery Update - Configured to use jQuery 1.7 or higher.

Libraries
 * CKEditor - Version 4.3 or later.
   http://ckeditor.com/download
 * CKEditor Widget plugin - Compatible with the installed version of CKEditor.
   http://ckeditor.com/addon/widget

INSTALLATION
------------

* Install Entity Embed via the standard Drupal installation process:
  'http://drupal.org/node/895232'.
* If you weren't previously using the CKEditor WYSIWYG client-side editor,
  download the CKEditor library (http://ckeditor.com/download) and extract it to
  'sites/all/libraries' or 'sites/sitename/libraries' as you require. The
  extracted folder must be named 'ckeditor'.
* Download the Widget plugin (http://ckeditor.com/addon/widget), extract it and
  move it into the 'plugins' directory of the 'ckeditor' folder so that it is
  available at 'ckeditor/plugins/widget'.
* Configure the jQuery Update module to use jQuery 1.7 or higher:
  '/admin/config/development/jquery_update'.
* Enable the entity-embed filter 'Display embedded entities' for the desired
  text formats from the Text Formats configuration page:
  '/admin/config/content/formats'.
* If the 'Limit allowed HTML tags' filter is enabled, add '<drupal-entity>' to
  the 'Allowed HTML tags'.
* Optionally enable the filter-align filter 'Align embedded entities' to allow
  positioning of embedded entities.
* To enable the WYSIWYG plugin, move the entity-embed 'E' button into the
  Active toolbar for the desired text formats from the CKEditor configuration
  page: '/admin/config/content/ckeditor'.

By default, Entity Embed includes a single button for embedding nodes.
Additional buttons can be added from the configuration page:
'/admin/config/content/embed-button'.

TECHNICAL DETAILS
-----------------

Users should be embedding entities using the CKEditor WYSIWYG button as
described above. This section is more technical about the HTML markup that is
used to embed the actual entity.

Embed by UUID (recommended: requires the UUID module):
<div data-entity-type="node" data-entity-uuid="07bf3a2e-1941-4a44-9b02-2d1d7a41ec0e" data-view-mode="teaser" />

Embed by ID (not recommended):
<div data-entity-type="node" data-entity-id="1" data-view-mode="teaser" />
