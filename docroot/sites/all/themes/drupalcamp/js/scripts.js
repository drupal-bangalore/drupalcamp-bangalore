var $ = jQuery.noConflict();
$(document).ready(function() { 
  var window_width = parseInt($(window).width());
  if ($('.bxslider-wrap .view-content').length > 0) {
    var slide_length = parseInt($('.bxslider-wrap .view-content .views-row').length);
    if (window_width < 641) {
      // Only 7 slides in mobile
      if (slide_length > 7) {
        while (slide_length > 7) {
          $('.bxslider-wrap .view-content .views-row').eq(7).remove();
          slide_length = parseInt($('.bxslider-wrap .view-content .views-row').length);
        }
      }
      $('.bxslider-wrap .view-content').bxSlider({
        auto: true,
        adaptiveHeight: true,
        controls: true,
        pause: 6000,
        autoStart: true,
        autoDirection: 'next',
        infiniteLoop: true,
        minSlides: 1,
        maxSlides: 1,
        nextText: '<div class="mouseOverRight"><span class="next">Next</span></div>',
        prevText:'<div class="mouseOverLeft"><span class="prev">Prev</span></div>',
      });
    }
    else {
      $('.bxslider-wrap .view-content').bxSlider({
        auto: true,
        pause: 6000,
        pager: true,
        mode: 'fade',
        infiniteLoop: true,
        autoStart: true,
        autoDirection: 'next',
        nextText: '<div class="mouseOverRight"><span class="next">Next</span></div>',
        prevText:'<div class="mouseOverLeft"><span class="prev">Prev</span></div>',
      });
    }
  }
  
  //Social Share
  $('.sharebuttons a').on('tap click', function(e) {
    e.preventDefault();
    window.open($(this).attr('href'), $(this).attr('target'), "width=800, height=600");
  });
});