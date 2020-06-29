clear
repeat=1
until [ $repeat -eq 0 ]
do
	echo -e "\e[44mMenu\e[0m\n\e[44m1. Create\e[0m\n\e[44m2. View\e[0m\n\e[44m3. Insert\e[0m\n4. Delete\n5. Modify\n6. Exit\nChoice:\e[0m"
	read choice
	case $choice in
	1)#case to create database
		touch data.lst
		echo -e "Address Book successfully created"
		;;
	2)#case to view database
		echo -e "Please find records in the following format:\nCustomer_Name Loan_Type Account_Number Interest_Rate"
		column -t -s' ' data.lst
		;;
	3)#case to insert record
		echo -e "Enter Customer_Name:"
		read name
		echo -e "Enter Loan_Type:"
		read loan
		echo -e "Enter Account_Number:"
		read acc
		echo -e "Enter Interese_Rate:"
		read interest
		echo "$name $loan $acc $interest" >> data.lst
		echo -e "Data successfully recorded"
		;;
	4)#case to delete record
		echo -e "Enter Customer_Name:"
		read name
		echo -e "Following records will be deleted:"
		grep "$name" data.lst
		grep -vw "$name" data.lst > data_temp.lst
		cat data_temp.lst > data.lst
		rm data_temp.lst	
		;;
	5)#case to modify record
		touch temp.lst
		echo ''>temp.lst
		echo -e "Enter Customer_Name of record to be modified:"
		read val_name
		echo -e "Choose the field to be modified\n1. Customer_Name\n2. Loan_Type\n3. Account_Number\n4. Interest_Rate\nChoice:"
		read field
		case $field in
		1)#case to change name
			echo -e "Enter new Customer_Name:"
			read new_name
			while IFS= read -r line
			do
				name=$(echo "$line" | cut -d' ' -f1)
				new_loan=$(echo "$line" | cut -d' ' -f2)
				new_acc=$(echo "$line" | cut -d' ' -f3)
				new_interest=$(echo "$line" | cut -d' ' -f4)
				if [ "$val_name" = "$name" ]
		   		then
					echo "$new_name $new_loan $new_acc $new_interest">>temp.lst
				else 
					echo $line>>temp.lst
				fi
			done<data.lst
			cat temp.lst>data.lst
			rm temp.lst
			;;
		2)#case to change loan type
			echo -e "Enter new Loan_Type:"
			read new_loan
			while IFS= read -r line
			do
				name=$(echo "$line" | cut -d' ' -f1)
				new_acc=$(echo "$line" | cut -d' ' -f3)
				new_interest=$(echo "$line" | cut -d' ' -f4)
				if [ "$val_name" = "$name" ]
		   		then
					echo "$name $new_loan $new_acc $new_interest">>temp.lst
				else 
					echo $line>>temp.lst
				fi
			done<data.lst
			cat temp.lst>data.lst
			rm temp.lst
			;;
		3)#case to change account number
			echo -e "Enter new Account_Number:"
			read new_acc
			while IFS= read -r line
			do
				name=$(echo "$line" | cut -d' ' -f1)
				new_loan=$(echo "$line" | cut -d' ' -f2)
				new_interest=$(echo "$line" | cut -d' ' -f4)
				if [ "$val_name" = "$name" ]
		   		then
					echo "$name $new_loan $new_acc $new_interest">>temp.lst
				else 
					echo $line>>temp.lst
				fi
			done<data.lst
			cat temp.lst>data.lst
			rm temp.lst
			;;
		4)#case to change interest rate
			echo -e "Enter new Interest_Rate:"
			read new_interest
			while IFS= read -r line
			do
				name=$(echo "$line" | cut -d' ' -f1)
				new_loan=$(echo "$line" | cut -d' ' -f2)
				new_acc=$(echo "$line" | cut -d' ' -f3)
				if [ "$val_name" = "$name" ]
		   		then
					echo "$name $new_loan $new_acc $new_interest">>temp.lst
				else 
					echo $line>>temp.lst
				fi
			done<data.lst
			cat temp.lst>data.lst
			rm temp.lst
			;;
				
		*)#case to handle invalid input
			echo -e "Invalid choice please try again";repeat=1
			;;
		esac
		;;
	6)repeat=0;;#case to exit
	*)echo -e "Invalid choice please try again";repeat=1#case to handle invalid input
	esac
done
