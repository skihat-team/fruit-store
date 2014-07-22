<?php

class IndexController extends AdminController {
    public function indexAction() {

    }

    public function loginAction() {
        # 如果当前提交请求。
        if ($this->isPost()) {
            $this['user'] = $this->form('user');
            $identity = array($this['user']['name'], $this['user']['password']);

            # 如果验证通过，SecurityFilter过滤器会自动跳转。
            if (!$this->security->authenticate($identity)) {
                $this->message('对不起，用户名或密码发生错误。', SKIHAT_MESSAGE_ERROR);
            }
        }
    }

    public function logoutAction() {
        $this->security->unRegister();
        $this->redirect('login');
    }

    public function actionFilters() {
        $filters = parent::actionFilters();
        $filters['security']['authenticates'] = 'indexAction';

        return $filters;
    }
}