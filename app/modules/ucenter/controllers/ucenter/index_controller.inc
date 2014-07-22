<?php

class IndexController extends UcenterController {
    public function indexAction() {

    }

    public function profileAction() {
        # 获取当前用户标识。
        $identity = $this->security->identity();

        if ($this->isPost()) {
            $this['user'] = new UcenterUser(array_merge($this->form('user'), array('id' => $identity->id)), true, true);
            if ($this['user']->save()) {
                $this->message('个人信息更新成功', SKIHAT_MESSAGE_SUCCESS);
                $this->redirect('index');
                return;
            }
        } else {
            $this['user'] = UcenterUser::fetch($identity->id);
        }
    }

    public function passwordAction() {
        if ($this->isPost()) {
            $pass = $this->form('user');
            $identity = $this->security->identity();

            if (UcenterUser::password($identity->id, $pass['old'], $pass['password'])) {
                $this->message('更新密码成功.', SKIHAT_MESSAGE_SUCCESS);
                $this->redirect('index');
            } else {
                $this->message('更新密码错误，请检查原有密码是否正确。', SKIHAT_MESSAGE_FAIL);
            }
        }
    }

    public function actionModels() {
        Skihat::import('ucenter.models.ucenter_user', SKIHAT_PATH_APP_MODULES);
    }
}