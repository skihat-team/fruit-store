<?php
# 导入文件上传资源文件。
Skihat::import('kernels.medias.media', SKIHAT_PATH_LIBRARY);

class FileController extends AdminController {
    public function indexAction() {
        $path = $this->query('path', '');
        $engine = Media::engine('default');
        $files = $engine->files($path, $this->query('order', 'NAME'));

        $filesAll = array(
            'current_url' => $engine->hostUrl . '/' . $path,
            'current_dir_path' => $path,
            'moveup_dir_path' => preg_replace('/(.*?)[^\/]+\/$/', '$1', $path),
            'total_count' => count($files),
            'file_list' => $files
        );

        $this->json(json_encode($filesAll));
    }

    public function uploadAction() {
        # KindEditor 的文件上传十分奇怪，这里要使用字符串响应。
        if ($url = Media::upload($this->file('imgFile'))) {
            $this->text(json_encode(array('error' => 0, 'url' => $url)));
        } else {
            $this->text(json_encode(array('error' => 1, 'message' => '图片文件上传失败，请检查图片大小和图片的类型(支持:gif、jpg、png）。')));
        }
    }
}