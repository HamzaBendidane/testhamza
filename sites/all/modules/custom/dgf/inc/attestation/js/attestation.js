(function($){
    jQuery(document).ready(function($) {
        if ($("input[name='modal']").val() === 'fin_saisie') {
            $("#modal-fin-saisie").modal({
                'show': true,
                'backdrop': false,
                'keyboard': false,
            });
        }
    });
})(jQuery)