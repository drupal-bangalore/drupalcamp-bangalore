(function ($) {
  $(document).ready(function() {
    // Social Share icons.
    $('.sharebuttons a').on('tap click', function(e) {
      e.preventDefault();
      window.open($(this).attr('href'), $(this).attr('target'), "width=800, height=600");
    });
  });
})(jQuery);
