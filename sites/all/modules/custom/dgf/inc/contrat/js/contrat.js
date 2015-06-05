(function($){
    jQuery(document).ready(function($) {
        $("#etape-cerfa").attr('src', $("input[name='cerfa-step']").val());
        $("#etape-cerfa").show();
        
        //-----------------------------------------
        // Les tooltips
        //-----------------------------------------
        $('#niveau_info').tooltip({
            placement : 'top'
        });
        $('#coef_info').tooltip({
            placement : 'top'
        });
        $('#group_info').tooltip({
            placement : 'top'
        });
        $('#pay_info').tooltip({
            placement : 'top'
        });

        //-----------------------------------------
        // le datepicker
        //-----------------------------------------
        // ATTENTION : le format du datepicker est renouvelé lors de son appel
        // pour le calcul de la durée de formation (sinon retour au format par défaut).
        jQuery('.datePicker').datepicker({
            format: 'dd/mm/yyyy',
            language: 'fr',
            orientation: 'right',
        }).on('changeDate', function(e) {
            //jQuery(this).datepicker('hide');
        });

		if (jQuery('#edit-monthly-gross-pay').attr('class') == 'form-text error'){
			jQuery('#edit-monthly-gross-pay').val(jQuery('input[name=min_monthly_gross_pay]').val());
		}
        //-----------------------------------------
        // affichage de la modale de validation
        //-----------------------------------------
        jQuery('#edit-quit').click(function() {
            $('#modalquit').show();
            return false;
        });
    });
})(jQuery)

//-----------------------------------------
// Calcul de la durée de formation
//-----------------------------------------
jQuery('#edit-date-begin').datepicker({format: 'dd/mm/yyyy',language: 'fr'}).bind("change", function () {
    var d1 = jQuery('#edit-date-begin').datepicker('getDate');
    var d2 = jQuery('#edit-date-end').datepicker('getDate');
    var diff = 0;

    if (d1 && d2) {
        diff = monthDiff(d1, d2);
    }
    jQuery('#edit-training-duration').val(diff);

});
jQuery('#edit-date-end').datepicker({format: 'dd/mm/yyyy', language: 'fr'}).bind("change", function () {
    var d1 = jQuery('#edit-date-begin').datepicker('getDate');
    var d2 = jQuery('#edit-date-end').datepicker('getDate');
    var diff = 0;

    if (d1 && d2) {
        diff = monthDiff(d1, d2);
    }
    jQuery('#edit-training-duration').val(diff);
});

// On retire l'attribut disable pour que les données saisies soient
// envoyées au serveur.
jQuery('form').bind('submit', function() {
    jQuery(this).find('select').removeAttr('disabled');
    jQuery(this).find('input').removeAttr('disabled');
});

jQuery('#edit-next').click(function() {
    jQuery(this).find('select').removeAttr('disabled');
    jQuery(this).find('input').removeAttr('disabled');
});

//-----------------------------------------
// Gestion du select de type de contrat
//-----------------------------------------
jQuery('#edit-type').change(function() {
    var text = jQuery('#edit-type option:selected').text();

    if (text == 'Renouvellement') {
        jQuery('#typeModal').show();
    }
});

function monthDiff(d1, d2) {
    var months;
    months = (d2.getFullYear() - d1.getFullYear()) * 12;
    months -= d1.getMonth() + 1;
    months += d2.getMonth() + 1;
    return months <= 0 ? 0 : months;
}
