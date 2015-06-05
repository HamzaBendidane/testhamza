(function($) {
    jQuery(document).ready(function($) {
        $("#etape-cerfa").attr('src', $("input[name='cerfa-step']").val());
        $("#etape-cerfa").show();
        
        // Les Datepickers
        gestDatepicker();
        
        // Les tooltips
        gestTooltips();

        //  Chargement
        gestTypeQualificaton();
        modifyAnnualDistribution();
        
        $('#edit-type-qualification').change(function() {
            // Changement de type de qualification
            gestTypeQualificaton();
        });
        
        $('#edit-training-start').change( function () {
            // Perte focus training-start 
            modifyAnnualDistribution();
        });
        $('#edit-date-exam').change( function () {
            // Perte focus date-exam
            modifyAnnualDistribution();
        });
        
        // Gestion de la liste des formations recurrentes
        manageFormationRecurrentes();
        

        // Gestion de la modal de formation interne
        manageModalInternalTraining();
        
        manageModalQuitter();
        
        manageAutocomplete();
    });
    
    
})(jQuery);

function manageAutocomplete() {
    jQuery("#edit-libelle").change(function() {
        jQuery("input[name='id_libelle']" ).val('');
    });
    jQuery("#edit-libelle").autocomplete({
        source: '/autocomplete/get-intitule-formation',
        dataType: 'json',
        minLength : 2,
        select: function( event, ui ) {
            jQuery("#edit-libelle" ).val( ui.item.data.libelle.trim());
            jQuery("input[name='id_libelle']" ).val(ui.item.data.id.trim());
            return false;
        }
    });
}

function manageModalQuitter() {
    // gestion de la modale de validation
    jQuery('#edit-quit').click(function() {
        jQuery("#modalquit").modal("show");
    });
}

function modifyAnnualDistribution() {
    AnneeDebut = 0;
    AnneeFin = 0;
    // controle des dates "Date de début de la formation" et "Date de l'examen"
    var dtRegex = new RegExp(/\b\d{1,2}[\/-]\d{1,2}[\/-]\d{4}\b/);
    
    var dated = jQuery('#edit-training-start').val();
    if(dtRegex.test(dated)) {
        var tab= (jQuery('#edit-training-start').val()).split("/");
        datedebut = new Date(tab[2] + '-' + tab[1] + '-' + tab[0]);
        AnneeDebut = datedebut.getUTCFullYear();
    };

    var datef = jQuery('#edit-date-exam').val();
    if(dtRegex.test(datef)) {
        var tab= (jQuery('#edit-date-exam').val()).split("/");
        datefin = new Date(tab[2] + '-' + tab[1] + '-' + tab[0]);
        AnneeFin = datefin.getUTCFullYear();
    };
    
    if( (AnneeDebut != 0) && (!isNaN(AnneeDebut))) {
        // Libellé des dates répartitions
        jQuery("[for='edit-year1']").text(AnneeDebut);
        jQuery("[for='edit-year2']").text(AnneeDebut + 1);
        jQuery("[for='edit-year3']").text(AnneeDebut + 2);
    }

    if((AnneeDebut != 0) && (!isNaN(AnneeDebut)) && (AnneeFin != 0) && (!isNaN(AnneeFin))) {
        // Affichage des textfileds
        var AnneeDebutP1 = AnneeDebut + 1;

        // Annee + 2
        if(AnneeDebutP1 >= AnneeFin) {
            jQuery('.form-item-year3').hide();
            jQuery('#edit-year3').val('');
        }
        else {
            jQuery('.form-item-year3').show();
        }
        // ANnee + 1
        if(AnneeDebut >= AnneeFin) {
            jQuery('.form-item-year1').hide();
            jQuery('#edit-year1').val('');
            jQuery('.form-item-year2').hide();
            jQuery('#edit-year2').val('');
            jQuery('#edit-annual-distribution').hide();
        }
        else {
            jQuery('.form-item-year1').show();
            jQuery('.form-item-year2').show();
            jQuery('#edit-annual-distribution').show();
        }
    }
    else {
        jQuery('#edit-annual-distribution').hide();
        jQuery('#edit-year1').val('');
        jQuery('#edit-year2').val('');
        jQuery('#edit-year3').val('');
    }
    
};

function manageModalInternalTraining() {
    // Affichage de la modal de formation interne 
    jQuery('#edit-internal-training').change(function() {
        if (jQuery('#edit-internal-training').is(':checked')) {
            jQuery("#modalinternaltraining").modal("show");
        }
    });
    
    // Quitter la modal
    jQuery('#internal_training_quit_modal').click(function() {
        jQuery("#modalinternaltraining").modal("hide");
    });
    
};

function gestTooltips() {

    jQuery('#total_duration_info').tooltip({
        placement : 'top'
    });
    
    jQuery('#duration_main_learning_info').tooltip({
        placement : 'top'
    });
    
    jQuery('#accompanying_actions_info').tooltip({
        placement : 'top'
    }); 
    
};


function gestDatepicker() {
    // le datepicker
    // ATTENTION : le format du datepicker est renouvelé lors de son appel
    // pour le calcul de la durée de formation, sinon retour au format par défaut.
    jQuery('.datePicker').datepicker({
        format: 'dd/mm/yyyy',
        language: 'fr',
    }).on('changeDate', function(e) {
       // jQuery(this).datepicker('hide');
        modifyAnnualDistribution();
    });
    
};


function gestTypeQualificaton () {
    // Gestion du type de qualification
    var idClassifReconnue = '#edit-type-qualification-3';
    var idCQPICQPM = '#edit-type-qualification-1';
    
    jQuery(idClassifReconnue).click(function() {
    	if(jQuery(idClassifReconnue).prop('checked')) {
    	        jQuery('#edit-internal-training').prop('checked', true);
    	        jQuery("#modalinternaltraining").modal("show");
    	}
    });
    
    // Affichage de N° CQPI/CQPM
    if (jQuery(idCQPICQPM).prop('checked') || jQuery(idClassifReconnue).prop('checked')) {
        jQuery('.form-item-num-CQPI-CQPM').show();
    }
    else {
        jQuery('.form-item-num-CQPI-CQPM').hide();
    }
    
}

function manageFormationRecurrentes() {
    // Gestion de la liste de formation récurrentes
    jQuery('.list-group-item').click(function() {
        var $element = jQuery(this);
        jQuery("#edit-libelle").val($element.text());
        if($element.data('id') != 0) {
            jQuery("input[name='id_libelle']").val( $element.data('id') );
        }
        else {
        	jQuery("input[name='id_libelle']").val( 0 );
        }
    });
}