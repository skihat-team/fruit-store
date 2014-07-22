<?php

class RegisterController extends UcenterController {
    public function indexAction() {
        if ($this->isPost()) {
            $this['user'] = new UcenterUser($this->form('user'));

            if ($this['user']->save()) {
                $this->security->register(UcenterUser::fetch($this['user']->key(), array(), Model::FETCH_STYLE_OBJ));
                $this->security->autoRedirect();
            } else {
                $this->message('注册账户失败，请检查账户字段值.', SKIHAT_MESSAGE_FAIL);
            }
        }
    }

    public function actionModels() {
        Skihat::import('ucenter.models.ucenter_user', SKIHAT_PATH_APP_MODULES);
    }

    public function actionFilters() {
        $filters = parent::actionFilters();
        $filters['security']['authenticates'] = false;

        return $filters;
    }
}