#!/usr/bin/env php

<?php

class App{

    private string $app_json;
    private string $app_log;
    private string $path;

    public function __construct()
    {

        $this->path = getenv("HOME");
        $this->app_json = $this->path . "/appmanager/app_command.json";
        $this->app_log = $this->path . "/appmanager/app_log.txt";
        
    }

    public function run(string $command, string $app_number) : void{

        if(!is_dir($this->path . "/appmanager")) mkdir($this->path . "/appmanager", 0755, true);

        if(!file_exists($this->app_json)) file_put_contents($this->app_json, "[]", LOCK_EX);

        match($command){

            "home" => $this->Home_command(),

            "add" => $this->Add_command(),

            "reset" => $this->Reset_command(),

            "delete" => $this->Delete_command(),

            "list" => $this->List_command(),

            "run" => $this->Run_command($app_number),

            default => (function(){

                echo "\n";
                echo "Command not found\n";
                echo "Use : app or php app\n";
                echo "Use : app list or php app list\n";
                echo "Use : app add or php app add\n";
                echo "Use : app delete or php app delete\n";
                echo "Use : .app reset or php app reset\n";

            })()

        };

    }

    private function Home_command(): void{

        echo "App:\n\n";

        //===================================
        // All app list
        //===================================

        $result = json_decode(file_get_contents($this->app_json), true) ?? []; 

        if(empty($result)){

            $this->save_log("INFO", "No Apps Found");

            echo "[INFO] No Apps Found.\n\n";

            echo "> First add an app:\n";
            echo "   app or php app add\n\n";

            echo "> Available commands:\n";
            echo "   app or php app list\n";
            echo "   app or php app add\n";
            echo "   app or php app delete\n";
            echo "   app or php app reset\n";

            exit;

        }

        foreach ($result as $data){

            $this->output($data["app_number"], $data["app_name"]);

        }

        echo "\n";
        echo "Selected number:\n";

        $user_number = readline("=>");      // user input

        $s_user_number = trim(preg_replace("/[^\p{N}]/", "", $user_number ?? ""));    //sanitize user input

        if(empty($s_user_number)){

            $this->save_log("ERROR", "Invalid number");

            echo "[ERROR] Invalid number\n";
            exit;

        }

        //search number
        $isFound = false;
        $app_name = "";
        $app_command = [];

        foreach ($result as $list){

            if(($list["app_number"] ?? null) == $s_user_number){

                $isFound = true;
                $app_name = $list["app_name"];
                $app_command = $list["app_command"];
                break;

            }

        }

        if(!$isFound){

            $this->save_log("ERROR", "Not Found");

            $this->app_print("[ERROR] Not Found");

        }

        echo "\033[H\033[J";

        echo "================================================\n";
        echo"$app_name\n";
        echo "================================================\n";
        
        foreach ($app_command as $command){

            if(!empty($command)){

                $this->save_log("COMMAND", "[$command] is executed");

                passthru(escapeshellcmd($command) . " 2>&1");

            }

        }

    }//fun end

    private function Add_command(): void{

        //initil items
        $number = "";
        $title = "";
        $first_command = "";
        $second_command = "";
        $third_command = "";
        $fourth_command = "";
        $fifth_command = "";

        $is_single_command = false;
        $is_multiple_command = false;

        echo "Select Command:\n";
        $this->output("1", "Single command");
        $this->output("2", "Multiple command");

        //user input
        echo "\n";
        $selected_number = readline("=>");
        echo "\n";

        if($selected_number === "1"){

            $is_single_command = true;

            echo "App selection number :\n";
            $number = readline("=>");
            echo "\n";

            echo "App title :\n";
            $title = readline("=>");
            echo "\n";

            echo "App command :\n";
            $first_command = readline("=>");


        }elseif($selected_number === "2"){

            $is_multiple_command = true;

            echo "App selection number :\n";
            $number = readline("=>");
            echo "\n";

            echo "App title :\n";
            $title = readline("=>");
            echo "\n";

            echo "1st command :\n";
            $first_command = readline("=>");
            echo "\n";

            echo "2nd command :\n";
            $second_command = readline("=>");
            echo "\n";

            echo "3rd command :\n";
            $third_command = readline("=>");
            echo "\n";

            echo "4th command :\n";
            $fourth_command = readline("=>");
            echo "\n";

            echo "5th command :\n";
            $fifth_command = readline("=>");

        }else{

            $this->save_log("ERROR", "Invalid Number");
            $this->app_print("[ERROR] Invalid Number");

        }

        //sanitizing data
        $s_number = trim(preg_replace("/[^\p{N}]/", "", $number ?? ""));
        $s_title = trim($title);
        $s1st_command = trim($first_command);
        $s2nd_command = trim($second_command);
        $s3th_command = trim($third_command);
        $s4th_command = trim($fourth_command);
        $s5th_command = trim($fifth_command);

        //empty data checks
        if($is_single_command){

            if(empty($s_number) || empty($s_title) || empty($s1st_command)){

                $this->save_log("ERROR", "[$number] [$title] [$first_command] Invalid Number / Text / Command");

                $this->app_print("[ERROR] Invalid Number / Text / Command");

            }

        }else{

            if((empty($s_number) || empty($s_title)) || (empty($s1st_command) && 
            empty($s2nd_command) && empty($s3th_command) && empty($s4th_command) && empty($s5th_command))){

                $this->save_log("ERROR", "[$number] [$title] [$first_command] [$second_command] [$third_command] [$fourth_command] [$fifth_command] Invalid Number / Text / Command");

                $this->app_print("[ERROR] Invalid Number / Text / Command");

            }

        }

        //check app in list

        $app_data = json_decode(file_get_contents($this->app_json), true) ?? [];

        if(!empty($app_data)){

            foreach ($app_data as $app){

                if(($app["app_number"] ?? null) == $s_number){

                    $this->save_log("ERROR", "[$s_number] Duplicate App Found");

                    $this->app_print("[ERROR] Duplicate App Found");

                }

            }

        }

        //insert user app in list

        if($is_single_command){

            $data = [

                "app_number" => $s_number,
                "app_name" => $s_title,
                "app_command" => [ $s1st_command ]

            ];

        }else{

            $data = [

                "app_number" => $s_number,
                "app_name" => $s_title,
                "app_command" => [ 

                    $s1st_command ?? "",
                    $s2nd_command ?? "",
                    $s3th_command ?? "",
                    $s4th_command ?? "",
                    $s5th_command ?? ""

                 ]

            ];

        }

        $app_data[] = $data;

        $insert = file_put_contents($this->app_json, json_encode($app_data, JSON_PRETTY_PRINT | 
        JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE), LOCK_EX);

        chmod($this->app_json, 0600);
            
        if(!$insert){

            $this->save_log("ERROR", "App Not Saved");

            $this->app_print("[ERROR] App Not Saved");

        }

        $this->save_log("OK", "App Saved Successful");

        $this->app_print("[OK] App Saved Successful");
            
    }//fun end

    private function Delete_command(): void{

        echo "App selection number:\n";

        $number = readline("=>"); //user input

        $s_number = trim(preg_replace("/[^\p{N}]/", "", $number ?? ""));  //sanitize number

        if(empty($s_number)){

            $this->save_log("ERROR", "[$number] Invalid Number");

            $this->app_print("[ERROR] Invalid Number");

        }

        //check app in list

        $app_data = json_decode(file_get_contents($this->app_json), true) ?? [];
        $isDeleted = false;

        if(!empty($app_data)){

            foreach ($app_data as $index => $app){

                if(($app["app_number"] ?? null) == $s_number){

                    unset($app_data[$index]);
                    $isDeleted = true;
                    break;

                }

            }

        }

        if($isDeleted){

            $app_data = array_values($app_data);

            file_put_contents($this->app_json, json_encode($app_data, JSON_PRETTY_PRINT | 
                JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE), LOCK_EX);

            $this->save_log("OK", "Delete Successful");

            $this->app_print("[OK] Delete Successful");

        }

        $this->save_log("ERROR", "Delete Failed");

        $this->app_print("[ERROR] Delete Failed");
        
    }//fun end

    private function Reset_command(): void{

        $isUserConfirmed = false;

        $data = json_decode(file_get_contents($this->app_json), true) ?? [];

        if(empty($data)){

            $this->save_log("INFO", "Empty App List");

            echo "[INFO] Empty App List\n\n";

            echo "> Add your first app:\n";
            echo "   app or php app add\n\n";
            exit;

        }

        echo "Are you sure you want reset all [Y/n]:\n";

        $input = readline("=>");    //user input

        $s_input = trim(preg_replace("/[^a-zA-Z]/", "", $input ?? ""));     //sanitize user input

        if(empty($s_input)){

            $this->save_log("ERROR", "[$input] Invalid Text");

            $this->app_print("[ERROR] Invalid Text");

        }

        if(strtolower($s_input) === "y"){

            $isUserConfirmed = true;

        }else{

            $isUserConfirmed = false;

        }

        if($isUserConfirmed){

            file_put_contents($this->app_json, "[]", LOCK_EX);

            $this->save_log("OK", "Reset Successful");

            $this->app_print("[OK] Reset Successful");

        }

        $this->save_log("ERROR", "Reset Failed");
        $this->app_print("[ERROR] Reset Failed");
            
    }//fun end

    private function List_command(): void{

        $green_color = "\033[32m";
        $bold_text = "\e[1m";
        $reset = "\e[0m";

        //all app list
            
        $app = json_decode(file_get_contents($this->app_json), true) ?? [];

        if(!empty($app)){

            echo " No  >> Name    >> Command\n\n";

            foreach ($app as $app_data){

                $number = $app_data["app_number"];
                $name = $app_data["app_name"];
                $command = $app_data["app_command"];

                $command = "[ " . implode(" ], [ ", $command) . " ]";

                printf(" %-3s >> %-15s >> %-70s \n", $number, $bold_text . $name . $reset, $green_color . $bold_text . $command . $reset);

            }


        }else{

            $this->save_log("INFO", "Empty App List");

            echo "[INFO] Empty App List\n\n";

            echo "> Add your first app:\n";
            echo "   app add or php app add\n\n";

        }

    }//fun end

    private function Run_command(string $app_number) : void{

        //=================================
        // Sanitizing the number
        //=================================
        $s_app_number = preg_replace("/[^\p{N}]/", "", $app_number);

        $app = json_decode(file_get_contents($this->app_json), true) ?? [];

        if(empty($s_app_number)){

            $this->app_print("[ERROR] Invalid Number");
            $this->save_log("ERROR", "[$app_number] Invalid Number");

        }

        if(!empty($app)){

            $isFound = false;
            $app_number = "";
            $app_command = [];

            //==============================
            // Search app number in list
            //==============================

            foreach ($app as $list){

                if(($list["app_number"] ?? null) == $s_app_number){

                    $isFound = true;
                    $app_number = $list["app_number"];
                    $app_command = $list["app_command"];
                    break;

                }

            }

            if(!$isFound){

                $this->app_print("[ERROR] App Not Found");
                $this->save_log("ERROR", "[$s_app_number] Not Found in List");

            }

            foreach ($app_command as $command){

                $this->save_log("[COMMAND]", "[$command] is executed");

                passthru(escapeshellcmd($command) . " 2>&1");

            }


        }else{

            $this->app_print("[ERROR] Not Found");
            $this->save_log("ERROR", "App List Not Found");

        }

    }//fun end

    private function output(string $number, string $text) : void{

        $bold_text = "\e[1m";
        $reset = "\e[0m";

        echo "[" . $bold_text . $number . $reset . "]" . " " . $bold_text . $text . $reset . "\n";

    }//fun end

    private function app_print(string $text) : void{

        echo "\n";
        echo "$text\n";
        exit;

    }//fun end

    private function save_log(string $type, string $message){

        date_default_timezone_set("UTC");

        $date = date("Y-m-d h:i:s A");

        $log = "[$date] >> [$type] >> $message";

        file_put_contents($this->app_log, $log . PHP_EOL, FILE_APPEND);

    }//fun end


}

$command = $argv[1] ?? "home";
$app_number = $argv[2] ?? "";
$app = new App();
$app->run($command, $app_number);

