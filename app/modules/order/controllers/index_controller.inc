<?php

class IndexController extends ApplicationController {
    public function indexAction() {
        # 更新商品价格。
        Cart::update();

        # 设置填充值。
        $this['cart'] = Cart::items();
        $this['total'] = Cart::total();
    }

    public function addAction() {
        if ($this->isPost()) {
            # 将商品信息加入购物车。
            if (Cart::add(intval($this->form('goods')), intval($this->form('amount')))) {
                $this->message('成功将商品添加到购物车。', SKIHAT_MESSAGE_SUCCESS);
            } else {
                $this->message('对不起，商品添加失败。', SKIHAT_MESSAGE_ERROR);
            }
        }

        $this->redirect('index');
    }

    public function removeAction() {
        if ($this->isPost()) {
            Cart::remove($this->form('goods'));

            $this->message('从购物车中移除商品信息成功。', SKIHAT_MESSAGE_SUCCESS);
        }

        $this->redirect('index');
    }

    public function changeAction() {
        if ($this->isPost()) {
            Cart::change($this->form('goods'), $this->form('amount'));
        }

        $this->text(sprintf(SKIHAT_I18N_CURRENCY, Cart::total()));
    }

    public function totalAction() {
        if ($amounts = Cart::amounts()) {
            $this->text(sprintf('有%d件商品', $amounts));
        } else {
            $this->text('没有任何商品');
        }
    }

    public function actionModels() {
        Skihat::import('order.services.cart', SKIHAT_PATH_APP_MODULES);
        Skihat::import('goods.models.goods', SKIHAT_PATH_APP_MODULES);
    }
}