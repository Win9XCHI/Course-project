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
//
//add
    if ($_POST['C'] == "1") {
        $content = 'C '. $_POST['C']. ' '. 'numTrain '. $_POST['num']. ' '. 'St_1 '. $_POST['St_1']. ' '. 'St_2 '. $_POST['St_2']. ' '. 'Col '. $_POST['Col']. ' '. 'Time '. $_POST['Time']. ' '. 'Type '. $_POST['Type']. ' '. 'Col_V '. $_POST['Col_V']."\n";
    }
    if ($_POST['C'] == "2") {
        $content = 'C '. $_POST['C']. ' '. 'cod '. $_POST['cod']. ' '. 'num_S '. $_POST['num_S']. ' '. 'Time_1 '. $_POST['Time_1']. ' '. 'Time_2 '. $_POST['Time_2']. ' '. 'num '. $_POST['num']. "\n";
    }
    if ($_POST['C'] == "3") {
            $content = 'C '. $_POST['C']. ' '. 'dat '. $_POST['dat']. ' '. 'T1 '. $_POST['T1']. ' '. 'T2 '. $_POST['T2']. ' '. 'num '. $_POST['num']. "\n";
        }
    if ($_POST['C'] == "4") {
            $content = 'C '. $_POST['C']. ' '. 'cod_V '. $_POST['cod_V']. ' '. 'num_V '. $_POST['num_V']. ' '. 'Type_V '. $_POST['Type_V']. ' '. 'num '. $_POST['num']. ' '. 'Col_V '. $_POST['Col_V']. ' '. 'Col '. $_POST['Col']. "\n";
        }
//
//del
    if ($_POST['C'] == "7") {
            $content = 'C '. $_POST['C']. ' '. 'Num '. $_POST['Num']. "\n";
        }
    if ($_POST['C'] == "8") {
            $content = 'C '. $_POST['C']. ' '. 'Num '. $_POST['Num']. ' '. 'S '. $_POST['S']. ' '. 'nC '. $_POST['nC']. "\n";
        }
    if ($_POST['C'] == "9") {
            $content = 'C '. $_POST['C']. ' '. 'Num '. $_POST['Num']. ' '. 'dat '. $_POST['dat']. "\n";
        }

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
            
            $stream = new FileReader("FileCheck.txt");
            echo $stream->ReadAll();
            exit;
        }
    }
?>