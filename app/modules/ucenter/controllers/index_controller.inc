<?php

class IndexController extends UcenterController {
    public function indexAction() {
        if ($this->isPost()) {
            $user = $this->form('user');

            if (!$this->security->authenticate(array($user['email'], $user['password']))) {
                $this->message('对不起，邮件或密码错误，请重试试。', SKIHAT_MESSAGE_FAIL);
            }
        }
    }

    public function logoutAction() {
        $this->security->unregister();
        $this->redirect('/');
    }

    public function statusAction() {
        if ($identity = $this->security->identity()) {
            $this->text(sprintf('<a title="进入会员中心" href="%s">%s</a> &nbsp;|&nbsp;<a title="退出登录" href="%s">退出</a> ',
                '/?package=ucenter&module=ucenter', $identity->name, '/?module=ucenter&action=logout'));
        } else {
            $this->text(sprintf('<a title="登录已有账户" href="%s">登录</a> &nbsp;|&nbsp; <a href="%s" title="免费注册">免费注册</a>',
                '/?module=ucenter', '/?module=ucenter&controller=register'));
        }
    }

    public function actionFilters() {
        $filters = parent::actionFilters();
        $filters['security']['authenticates'] = false;

        return $filters;
    }
}