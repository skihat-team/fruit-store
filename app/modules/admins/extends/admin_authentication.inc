<?php
Skihat::import('admins.models.admins_user', SKIHAT_PATH_APP_MODULES);

class AdminAuthentication implements IAuthentication {
    function authenticate($identity) {
        list($user, $pass) = $identity;
        return AdminsUser::authenticate($user, $pass);
    }
}