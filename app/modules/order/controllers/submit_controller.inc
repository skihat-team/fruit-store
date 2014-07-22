<?php

class SubmitController extends UcenterController {
    public function indexAction() {
        # 如果购物车中没有任何商品。
        if (Cart::amounts() < 1) {
            $this->message('当前购物车里没有任何商品信息.', SKIHAT_MESSAGE_WARNING);
            $this->redirect(array(SKIHAT_PARAM_CONTROLLER => 'index', SKIHAT_PARAM_ACTION => 'index'));
            return;
        }

        if ($this->isPost()) {
            $identity = $this->security->identity();
            $this['order'] = new Order($this->form('order'));
            if ($result = Transfer::submit($this['order'], Cart::items(), $identity->id)) {
                Cart::clear();

                $this->message(array('提交订单成功，共购物%d件商品，总价%.2f', $result[0], $result[1]), SKIHAT_MESSAGE_SUCCESS);
                $this->redirect('complete');
                return;
            }
        }

        # 更新产品价格，并设置显示内容。
        Cart::update();
        $this['cart'] = Cart::items();
        $this['total'] = Cart::total();
    }

    public function completeAction() {

    }

    public function actionModels() {
        Skihat::import('order.models.order', SKIHAT_PATH_APP_MODULES);
        Skihat::import('order.services.cart', SKIHAT_PATH_APP_MODULES);
        Skihat::import('order.services.transfer', SKIHAT_PATH_APP_MODULES);
    }
}