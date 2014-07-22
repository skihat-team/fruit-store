<?php
Skihat::import('ucenter.models.ucenter_user', SKIHAT_PATH_APP_MODULES);

class UcenterAuthentication implements IAuthentication {
    public function authenticate($identity) {
        list($email, $password) = $identity;
        return UcenterUser::authenticate($email, $password);
    }
}