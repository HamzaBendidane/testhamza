(function($){
    jQuery(document).ready(function($) {
    	// ----------------------------------
        // Modale de suppression 
        // ----------------------------------
        $('body').on('click', '.modalQuit', function() {
            $('#deleteModal').hide();
            $('#delete-info-name').html('');
        	$('#delete-info-siret').html('');
        });

        // On remplit le corps de la modale selon l'élément cliqué
        $('body').on('click', '.listBtn', function() {
        	siret = $(this).data('siret');
        	name = $(this).data('name');
        	// On affiche le siret et la raison sociale dans la popup 
        	$('#delete-info-name').html(name);
        	$('#delete-info-siret').html(siret);
        	// On ajoute l'id de l'établissement à supprimer au bouton de supression
        	id = $(this).data('id');
        	$('#edit-modal-delete').attr('data-id', id);
        });

        $('body').on('click', '#edit-modal-delete', function() {
        	$id = $('#edit-modal-delete').data('id');
            jQuery.ajax({
                cache: false,
                type: 'GET',
                url: '/ajax/gestion/etablissement/delete' + '/' + $id,
                //data: {id: $id}, //, user: user
                dataType: 'text',
                error: function(request, status, error) {
                    alert(status);
                },
                success: function(data, status, request) {
                	alert('prourt');
                	refreshTable();
                }
            });
        });

        $('body').on('click', '#edit-search', function() {
             refreshTable();
        });

        $('body').on('click', '#edit-reset', function() {
            $('#edit-siret').val('');
            $('#edit-corporate-name').val('');
            $('#edit-responsible-name').val('');
            refreshTable();
        });
        refreshTable();
        // ----------------------------------
        // Autocompletion
        // ----------------------------------
        $('body').on('click', '#edit-siret', function() {
            $('#edit-siret').autocomplete({
                  source: '/gestion/etablissement/list/autocomplete/siret',
                  dataType: 'json',
                  minLength : 3,
            });
        });
        $('body').on('click', '#edit-corporate-name', function() {
            $('#edit-corporate-name').autocomplete({
                source: '/gestion/etablissement/list/autocomplete/corporate-name',
                dataType: 'json',
                minLength : 3,
            });
        });
        $('body').on('click', '#edit-responsible-name', function() {
            $('#edit-responsible-name').autocomplete({
                source: '/gestion/etablissement/list/autocomplete/responsible-name',
                dataType: 'json',
                minLength : 3,
            });
        });
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
        url: '/gestion/etablissement/list/pager',
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