(function($){
    jQuery(document).ready(function($) {
    	// ----------------------------------
        // Modale de suppression 
        // ----------------------------------
        $('body').on('click', '#edit-search', function() {
             refreshTable();
        });
        refreshTable();
        autocompletefilter();
    });
})(jQuery)

function refreshTable(page, sort, order, siret, corporateName, responsibleName) { //, siret, corporateName, responsibleName
    if(!page) page = 0;
    if(!sort) sort = '';
    if(!order) order = '';
    if(!siret) siret = '';
    if(!corporateName) corporateName = '';
    if(!responsibleName) responsibleName = '';

    if (jQuery('#edit-siret').length > 0) siret = jQuery('#edit-siret').val();
    if (jQuery('#edit-corporate-name').length > 0) corporateName = jQuery('#edit-corporate-name').val();
    if (jQuery('#edit-responsible-name').length > 0) responsibleName = jQuery('#edit-responsible-name').val();

    jQuery.ajax({
        cache: false,
        type: 'GET',
        url: '/validation/etablissement/list/pager',
        data: {page: page, sort: sort, order: order, siret: siret, corporateName: corporateName, responsibleName: responsibleName},
        dataType: 'text',
        error: function(request, status, error) {
            alert(status);
        },
        success: function(data, status, request) {
            var html = data;

            jQuery('#table-container').html(html);
            
            jQuery('#table-container th a').
                add('#table-container .pager-item a')
                .add('#table-container .pager-first a')
                .add('#table-container .pager-previous a')
                .add('#table-container .pager-next a')
                .add('#table-container .pager-last a')
                    .click(function(el, a, b, c) {
                        var url = jQuery.url(el.currentTarget.getAttribute('href'));
                        refreshTable(
                            url.param('page'), url.param('sort'), url.param('order'),
                            url.param('siret'), url.param('corporateName'),
                            url.param('responsibleName')
                        );

                        return (false);
                    });
            jQuery(".sticky-enabled").css('min-width', '100%');
            
            // On crée la modal via jQuery pour l'insérer au bon endroit dans la page
            var modal = '<div id="deleteModal" class="modal" tabindex="-1" role="dialog" aria-hidden="true"> <div class="modal-dialog">';
            modal += '<div class="modal-content"><div class="modal-header"><button type="button" class="close modalQuit" data-dismiss="modal" aria-hidden="true">&times;</button>';
            modal += '<h4 class="modal-title">Voulez vous supprimer cet établissement ?</h4></div><div class="modal-body" id="modal-delete-body">';
            modal += '<label>Raison sociale</label><span id="delete-info-name"></span><br /><br /><label>SIRET</label><span id="delete-info-siret"></span>'; // <div class="row">
            modal += '</div><div class="modal-footer">';
            modal += '<input class="btn btn-default modalQuit" data-dismiss="modal" type="button" id="edit-modal-quit" value="Annuler">';
            modal += '<input class="btn btn-default modalValid form-submit" data-dismiss="modal" type="button" id="edit-modal-delete" value="Supprimer">';
            modal += '</div></div><!-- /.modal-content --></div><!-- /.modal-dialog --></div><!-- /.modal -->';
            // Afin d'éviter le chargement en double de la modal
            if (jQuery("#deleteModal").length == 0 ) {
                jQuery('#container').append(modal);
            }
        }
    });
}

function autocompletefilter() {
	// ----------------------------------
    // Autocompletion
    // ----------------------------------
    jQuery('body').on('click', '#edit-siret', function() {
        jQuery('#edit-siret').autocomplete({
              source: '/get/etablissement/autocomplete/siret',
              dataType: 'json',
              minLength : 3,
        });
    });
    jQuery('body').on('click', '#edit-corporate-name', function() {
        jQuery('#edit-corporate-name').autocomplete({
            source: '/get/etablissement/autocomplete/corporate-name',
            dataType: 'json',
            minLength : 3,
        });
    });
    jQuery('body').on('click', '#edit-responsible-name', function() {
        jQuery('#edit-responsible-name').autocomplete({
            source: '/get/etablissement/autocomplete/responsible-name',
            dataType: 'json',
            minLength : 3,
        });
    });
}

//function actionButton() {
//	$( ".selected" ).each(function(index) {
//	    $(this).on("click", function(){
//	        // For the boolean value
//	        var boolKey = $(this).data('selected');
//	        // For the mammal value
//	        var mammalKey = $(this).attr('id'); 
//	    });
//	});
//}