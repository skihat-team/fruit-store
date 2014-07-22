<?php

class ProfileController extends AdminController {
    public function indexAction() {
        if ($this->isGet()) {
            $this['user'] = AdminsUser::fetch($this['identity']->id);
        } else {
            $this['user'] = new AdminsUser(array_merge($this->form('user'), array('id' => $this['identity']->id)), true, true);
            if ($this['user']->save(array(Model::SYNTAX_FIELDS => array('password')))) {
                $this->message('更新个人密码成功.', SKIHAT_MESSAGE_SUCCESS);
                $this->redirect('index');
            }
        }
    }

    public function actionModels() {
        Skihat::import('admins.models.admins_user', SKIHAT_PATH_APP_MODULES);
    }
}