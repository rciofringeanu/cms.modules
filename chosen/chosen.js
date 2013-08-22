(function($) {
  Drupal.behaviors.chosen = {
    attach: function(context) {
      $(Drupal.settings.chosen.selector, context).each(function() {
        if ($(this).find('option').size() >= Drupal.settings.chosen.minimum) {
          $(this).chosen({
            placeholder_text: Drupal.t('Any'),
            placeholder_text_multiple: Drupal.t('Any'),
            placeholder_text_single: Drupal.t('Any'),
            no_results_text: Drupal.t('No results match'),
            search_contains: true,
          });
        }
      }); 
    }
  }

})(jQuery);