-- SUMMARY --

The Scald Extra module adds some extra useful functionality related to the Scald
module ecosystem. Currently it provides the following functionality to module
users:

* Automatically generate scald contexts for image styles that render the atom as
  its image only. This is useful for being able to easily render an atom image
  in the desired image style when referencing an atom in a node view mode or
  embedded in text on a WYSIWYG editor.

* Generate thumbnails for image styles when uploading an image for an atom. This
  can help prevent performance issues when a lot of images are uploaded, and to
  avoid problems that happen sometimes with the thumbnails not being generated
  until the next time the cache is cleared.

For a full description of the module, visit the project page:
  http://drupal.org/project/scald_extra

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/scald_extra


-- REQUIREMENTS --

None.


-- INSTALLATION --

* Install as usual, see http://drupal.org/node/895232 for further information.


-- CONFIGURATION --

* Go to admin/config/content/scald/extra and configure as desired.


-- CONTACT --

Current maintainers:
* Dimitris Bozelos (krystalcode) - http://drupal.org/user/2392706
