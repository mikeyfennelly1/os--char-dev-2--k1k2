#!/bin/bash

build_dir="../build"

function move_files_by_extension() {
    local extension="$1"
    local target_dir="$2"

    mkdir -p "$target_dir"

    # Use 'glob' expansion safely
    for file in *"$extension"; do
        [ -e "$file" ] && mv "$file" "$target_dir"
    done
}

move_files_by_extension ".o" "${build_dir}/objs"
move_files_by_extension ".ko" "${build_dir}/k_objs"
