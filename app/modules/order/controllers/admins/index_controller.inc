<?php

class IndexController extends AdminController {

    public function indexAction() {
        $conditions = array();

        if ($q = $this->query('q')) {
            if (is_numeric($q)) {
                $conditions['Order.id'] = intval($q);
            } else {
                $conditions['Order.consignee'] = addslashes($q);
            }
        }
        if ($status = $this->query('status')) {
            $conditions['Order.status'] = intval($status);
        }

        $this['orders'] = Order::fetchAll($conditions);
    }

    public function processAction() {
        if ($this->isPost()) {
            $conditions = array('Order.id' => intval($this->query('id')));
            switch ($this->form('action')) {
                case 'shopping':
                    Order::shoppingAll($conditions);
                    break;
                case 'complete':
                    Order::completeAll($conditions);
                    break;
                case 'trash':
                    Order::trashAll($conditions);
                    break;
            }

            $this->message('处理发订单信息。', SKIHAT_MESSAGE_SUCCESS);
            $this->redirect('index', true);
            return;
        }

        $this['order'] = Order::fetch(intval($this->query('id')));
        $this['items'] = OrderItem::fetchAll(array('order' => intval($this->query('id'))));
    }

    public function actionModels() {
        Skihat::import('order.models.order', SKIHAT_PATH_APP_MODULES);
        Skihat::import('order.models.order_item', SKIHAT_PATH_APP_MODULES);
    }

    public function actionFilters() {
        $filters = parent::actionFilters();
        $filters['paginate'] = array(
            SKIHAT_IOC_CLASS => 'controllers.filters.paginate_filter',
            SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
            'var' => 'orders'
        );

        return $filters;
    }
}