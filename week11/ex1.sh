# Create a file lofs.img not les than 50 MB
fallocate -l 50M lofs.img
# Setup a loop device on the file create
sudo losetup -f lofs.img
# Create a loop file systems (LOFS) ext4 on the file created
sudo mkfs -t ext4 lofs.img
# create a new directory ./lofsdisk
mkdir ./lofsdisk
# Mount the file created on the directory ./lofsdisk
sudo mount -o rw lofs.img ./lofsdisk
# Add two files file1 and file2 to the LOFS
sudo sh -c 'echo "Mohamed Ayoub" > ./lofsdisk/file1'
sudo sh -c 'echo "Eleuch" > ./lofsdisk/file2'
# Define a function to get the paths of shared libraries of a binary file
get_libs(){
    ldd $1 | awk '{print $3}'
}
# Get shared libraries of commands [bash, cat, echo, ls] and add them with their
# shared libraries to the LOFS
for command in bash cat echo ls; do
    libs=$(get_libs $(which $command))
    sudo cp $libs ./lofsdisk/
done
# Compile the file ex1.c
gcc ex1.c -o ex1
# Copy to the chroot directory
sudo cp ex1 ./lofsdisk/
# Change the root directory of the process to the mount point of the created LOFS
# and run the program ex1 and append the output to the file ex1.txt
sudo chroot ./lofsdisk /ex1 > ex1.txt
# Run the program ex1 without changing the root directory and append the output to
# the file ex1.txt
sudo ./ex1 > ex1.txt
