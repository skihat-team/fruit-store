<?php
/**
 * index_controller.inc 默认控制器声明。
 *
 * @copyright 2012-2013 Skihat team (skihat.cn)
 * @license   http://skihat.cn/license.html
 * @author    Skihat Team
 *
 * @package   app.controllers
 * @version   1.0
 *
 * @created   2012-08-07
 * @modified  2013-08-12
 */

/**
 * 示例默认控制器，提供默认服务。
 *
 * @package app.controllers
 */
class IndexController extends ApplicationController {
    public function indexAction() {
        $this['goodsAll'] = Goods::fetchHomeAll();
    }

    public function aboutAction() {

    }

    public function actionModels() {
        Skihat::import('goods.models.goods', SKIHAT_PATH_APP_MODULES);
    }

    public function actionFilters() {
        return array('cacheFilter' => array(
            SKIHAT_IOC_PATHS => SKIHAT_PATH_LIBRARY,
            SKIHAT_IOC_CLASS => 'controllers.filters.cache_filter',
            'actionMethods'  => array('indexAction', 'aboutAction')
        ));
    }
}