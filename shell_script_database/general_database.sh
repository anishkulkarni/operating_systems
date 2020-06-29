clear
repeat=1
until [ $repeat -eq 0 ]
do
	echo -e "\e[37m\e[44mMenu\n1. Create\n2. View\n3. Insert\n4. Delete\n5. Modify\n6. Exit\nChoice:\e[0m"
	read choice
	case $choice in
	1)touch data.lst;echo -e "\e[37m\e[41mAddress Book successfully created\e[0m";;
	2)
		echo -e "\e[37m\e[41mPlease find records in the following format:\nName Email Mobile\e[0m"
		column -t -s' ' data.lst
		;;
	3)
		echo -e "\e[37m\e[42mEnter name:\e[0m"
		read name
		echo -e "\e[37m\e[42mEnter email:\e[0m"
		read email
		echo -e "\e[37m\e[42mEnter mobile number:\e[0m"
		read mobile
		echo "$name $email $mobile" >> data.lst
		echo -e "\e[37m\e[41mData successfully recorded\e[0m"
		;;
	4)
		echo -e "\e[37m\e[42mEnter name:\e[0m"
		read name
		echo -e "\e[37m\e[42mFollowing records will be deleted:\e[0m"
		grep "$name" data.lst
		grep -vw "$name" data.lst > data_temp.lst
		cat data_temp.lst > data.lst
		rm data_temp.lst	
		;;
	5)
		echo -e "\e[37m\e[42mEnter name of record to be modified:\e[0m"
		read val_name
		echo -e "\e[37m\e[42mChoose the field to be modified\n1. Name\n2. Email\n3. Mobile\nChoice:\e[0m"
		read field
		case $field in
		1)
			echo -e "\e[37m\e[42mEnter new name:\e[0m"
			read new_name
			while IFS= read -r line
			do
				name=$(echo "$line" | cut -d' ' -f1)
				new_email=$(echo "$line" | cut -d' ' -f2)
				new_mobile=$(echo "$line" | cut -d' ' -f3)
				if [ "$val_name" = "$name" ]
		   		then
					echo "$new_name $new_email $new_mobile">>temp.lst
				else 
					echo $line>>temp.lst
				fi
			done<data.lst
			cat temp.lst>data.lst
			rm temp.lst
			;;
		2)
			echo -e "\e[37m\e[42mEnter new email:\e[0m"
			read new_email
			while IFS= read -r line
			do
				name=$(echo "$line" | cut -d' ' -f1)
				new_mobile=$(echo "$line" | cut -d' ' -f3)
				if [ "$val_name" = "$name" ]
		   		then
					echo "$name $new_email $new_mobile">>temp.lst
				else 
					echo $line>>temp.lst
				fi
			done<data.lst
			cat temp.lst>data.lst
			rm temp.lst
			;;
		3)
			echo -e "\e[37m\e[42mEnter new mobile number:\e[0m"
			read new_mobile
			while IFS= read -r line
			do
				name=$(echo "$line" | cut -d' ' -f1)
				new_email=$(echo "$line" | cut -d' ' -f2)
				if [ "$val_name" = "$name" ]
		   		then
					echo "$name $new_email $new_mobile">>temp.lst
				else 
					echo $line>>temp.lst
				fi
			done<data.lst
			cat temp.lst>data.lst
			rm temp.lst
			;;
				
		*)
			echo -e "\e[37m\e[41mInvalid choice please try again\e[0m";repeat=1
			;;
		esac
		;;
	6)repeat=0;;
	*)echo -e "\e[37m\e[41mInvalid choice please try again\e[0m";repeat=1
	esac
done
