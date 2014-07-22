<?php
# 引用框架控制器类。
Skihat::import('controllers.controller', SKIHAT_PATH_LIBRARY);

# 声明应用控制器，提供网站前台控制器的基础支持。
class ApplicationController extends Controller {
    public function actionView() {
        return array(
            SKIHAT_IOC_CLASS => self::DEFAULT_VIEW_CLASS,
            SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
            'theme' => 'defaults'
        );
    }
}

# 声明用户中心控制器，提供用户中心的基础支持。
class UcenterController extends Controller {
    public function actionFilters() {
        return array('security' => array(
            SKIHAT_IOC_CLASS => 'controllers.filters.security_filter',
            SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
            'authentication' => 'ucenter', 'authenticates' => '*',
            'loginUrl' => array('package' => null, 'module' => 'ucenter', 'controller' => 'index', 'action' => 'index'),
            'defaultUrl' => array('package' => 'ucenter', 'module' => 'ucenter', 'controller' => 'index', 'action' => 'index')
        ));
    }

    public function actionView() {
        return array(
            SKIHAT_IOC_CLASS => self::DEFAULT_VIEW_CLASS,
            SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
            'theme' => 'defaults'
        );
    }
}

# 声明管理控制器，提供后台管理支持。
class AdminController extends Controller {
    public function actionFilters() {
        return array('security' => array(
            SKIHAT_IOC_CLASS => 'controllers.filters.security_filter',
            SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
            'authentication' => 'admins', # 使用admins作为登录的安全验证提供者。
            'authenticates' => '*', # 所有活动必须登录。
            'loginUrl' => array('package' => 'admins', 'module' => 'admins', 'controller' => 'index', 'action' => 'login'),
            'defaultUrl' => array('package' => 'admins', 'module' => 'admins', 'controller' => 'index', 'action' => 'index')
        ));
    }

    public function actionView() {
        return array(
            SKIHAT_IOC_CLASS => self::DEFAULT_VIEW_CLASS,
            SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
            'theme' => 'admins'
        );
    }
}