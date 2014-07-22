<?php

class IndexController extends UcenterController {
    public function indexAction() {
        $identity = $this->security->identity();
        $this['orders'] = Order::fetchAll(array('Order.user' => $identity->id));
    }

    public function detailAction() {

    }

    public function actionModels() {
        Skihat::import('order.models.order', SKIHAT_PATH_APP_MODULES);
    }

    public function actionFilters() {
        $filters = parent::actionFilters();
        $filters['paginate'] = array(
            SKIHAT_IOC_CLASS => 'controllers.filters.paginate_filter',
            SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
            'sort' => 'Order.status,Order.id desc',
            'size' => 5,
            'var' => 'orders'
        );

        return $filters;
    }
}