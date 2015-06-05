
function refreshTable(page, sort, order) {
	if(!page) page = 0;
	if(!sort) sort = '';
	if(!order) order = '';
	actionNumber = null;
	actionNature = null;
	actionState = null;
	yearExercise = null;
	workerName = null;
	etablishment = null;
	if (jQuery('#edit-action-number').length > 0) actionNumber = jQuery('#edit-action-number').val();
	if (jQuery('#edit-action-nature').length > 0) actionNature = jQuery('#edit-action-nature').val();
	if (jQuery('#edit-action-state').length > 0) actionState = jQuery('#edit-action-state').val();
	if (jQuery('#edit-action-year-exercise').length > 0) yearExercise = jQuery('#edit-action-year-exercise').val();
	if (jQuery('#edit-worker-name').length > 0) workerName = jQuery('#edit-worker-name').val();
	if (jQuery('#edit-etablishment').length > 0) etablishment = jQuery('#edit-etablishment').val();

	jQuery.ajax({
		cache: false,
		type: 'GET',
		url: '/dgf/suivi/demande/pager',
		data: {page: page, sort: sort, order: order, actionNumber: actionNumber, actionNature: actionNature, actionState: actionState,
			yearExercise: yearExercise, workerName: workerName, etablishment: etablishment},
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
				.add('#edit-filter')
				.add('#edit-reset')
					.click(function(el, a, b, c) {
						var url = jQuery.url(el.currentTarget.getAttribute('href'));
						refreshTable(url.param('page'), url.param('sort'), url.param('order'));

						return (false);
					});
		}
	});
}


(function($){
	jQuery(document).ready(function($) {
		jQuery('#edit-reset').click(function() {
			jQuery('#edit-action-number').val('');
			jQuery('#edit-action-nature').val('');
			jQuery('#edit-action-state').val('');
			jQuery('#edit-action-year-exercise').val('');
			jQuery('#edit-worker-name').val('');
			jQuery('#edit-etablishment').val('');
		});
		refreshTable();
	});
})(jQuery)