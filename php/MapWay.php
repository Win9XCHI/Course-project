<?php
final class FileReader {
    protected $handler = null;
    protected $fbuffer = "";

    public function __construct($filename) {
        if(!($this->handler = fopen($filename, "rb")))
            throw new Exception("Cannot open the file");
    }

    public function ReadAll() {
    
        if(!$this->handler)
            throw new Exception("Invalid file pointer");
        
        while(!feof($this->handler))
            $this->fbuffer .= fgets($this->handler);
        
        return $this->fbuffer;
    }

    public function SetOffset($line) {
        if(!$this->handler)
            throw new Exception("Invalid file pointer");
        
        while(!feof($this->handler) && $line--) {
            fgets($this->handler);
        }
    }
};

    $error = "";
    $content = 'C '. '20 '. 'Num '. $_POST['Num']. ' '. 'St_1 '. $_POST['St_1']. ' '. 'St_2 '. $_POST['St_2']. "\n";

    if (!$handle = fopen("dataIndex.txt", "wb")) {
        $error = "C1 (Not open file)";
        exit;
    }
    else {
        if (fwrite($handle, $content) === FALSE) {
            $error = "C11 (Not write file)";
            exit;
        }
        else {
            fclose($handle);
            $programC = system('SearchWay.exe', $retval);
            echo $error;
            
            $stream = new FileReader("File.txt");
            echo $stream->ReadAll();
            exit;
        }
    }
?>
