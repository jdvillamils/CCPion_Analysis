#!/bin/bash

# Function to find the maximum number of lines in the files
find_max_lines() {
    local max_lines=0
    for file in *_total.txt; do
        lines=$(wc -l < "$file")
        if ((lines > max_lines)); then
            max_lines=$lines
        fi
    done
    echo "$max_lines"
}

# Function to handle the second loop and remove files with fewer lines
handle_second_loop() {
    local max_lines=$1
    local files=(
        nuevarsNT_total.txt
        numpivtxvarsNT_total.txt
        thetavarsNT_total.txt
        alphavarsNT_total.txt
        runvars_total.txt
        energiesvarsNT_total.txt
        energiesALLvarsNT_total.txt
        visenergiesALLvarsNT_total.txt
        recovars_total.txt
        pronglengthvars_total.txt
        pronghitshvars_total.txt
        coorstartvars_total.txt
        dirprongtvars_total.txt
        calenergiesvars_total.txt
        pdgntvars_total.txt
        pdgpngvars_total.txt
        cvnvars_total.txt
        trkNTvars_total.txt
        trkvars_total.txt
    )

    for file in "${files[@]}"; do
        lines=$(wc -l < "$file")
        if ((lines < max_lines)); then
            echo "File $file has fewer lines than the maximum."
            first_part=$(echo "$file" | cut -d '_' -f 1)
            echo "Checking the mini files $first_part"
            # Construct the pattern for matching files
            pattern="${first_part}.*.txt"
            # Iterate over files matching the pattern
            for mini_file in $pattern; do
                lines=$(wc -l < "$mini_file")
                #echo "File $mini_file has $lines lines."
                if ((lines == 0)); then
                    echo "File $mini_file has 0 lines."
                    # Extract the number from the filename
                    number=$(echo "$mini_file" | cut -d '.' -f 2 | cut -d '_' -f 1)
                    echo "Deleting all the files with flag: $number"
                    # Remove files with the extracted number
                    rm -rf *.$number*.txt
                    if [ $? -eq 0 ]; then
                        echo "Files deleted."
                    else
                        echo "No files to delete. Exiting loop."
                        return
                    fi
                fi
            done
        fi
    done
}

filesglobal=(
        nuevarsNT_total.txt
        numpivtxvarsNT_total.txt
        thetavarsNT_total.txt
        alphavarsNT_total.txt
        runvars_total.txt
        energiesvarsNT_total.txt
        energiesALLvarsNT_total.txt
        visenergiesALLvarsNT_total.txt
        recovars_total.txt
        pronglengthvars_total.txt
        pronghitshvars_total.txt
        coorstartvars_total.txt
        dirprongtvars_total.txt
        calenergiesvars_total.txt
        pdgntvars_total.txt
        pdgpngvars_total.txt
        cvnvars_total.txt
        trkNTvars_total.txt
        trkvars_total.txt
    )

# Main script
while true; do
    #Check if the files have different number of lines
    echo "Checking if all the files have the same number of lines"

    same_line_count=true
    previous_line_count=0

    for file in "${filesglobal[@]}"; do
        current_line_count=$(wc -l < "$file")
        #echo "$current_line_count"
        if [[ $previous_line_count -ne 0 && $current_line_count -ne $previous_line_count ]]; then
            same_line_count=false
            break
        fi
        previous_line_count=$current_line_count
    done

    if $same_line_count; then
        echo "All files have the same number of lines."
        for file in "${files[@]}"; do
            lines=$(wc -l < "$file")
            echo "$lines lines in File $file"
        done
        break
    fi

    echo "Well, not all have the same number of lines, starting debugging"

    max_lines=$(find_max_lines)
    echo "Maximum number of lines in the files: $max_lines"
    handle_second_loop "$max_lines"
    # Check if all files have the same number of lines

    echo "Allmini files deleted. I will merge again the files"
    echo "deleting"
    rm -rf *_total.txt
    echo "Doing the merge, this takes some time"
    . mergemain1.sh
    wait
    echo "All merged, starting again"
    
done
