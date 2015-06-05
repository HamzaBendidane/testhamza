(function($){
    jQuery(document).ready(function($) {
        if ($("input[type=radio][name=nature_demande]").val() != 'Action de formation') {
            $(".form-item-nature-formation").hide();
        }
        $("input[type=radio][name=nature_demande]").change(function() {
          $(".form-item-nature-formation, .radio-separator").toggle($(this).val() == '2');
        })
        $("#etape-cerfa").attr('src', $("input[name='cerfa-step']").val());
        $("#etape-cerfa").show();
    });
})(jQuery)