#!/usr/bin/env ruby

# fix_deps.rb

# Topaz Labs
# @author: Ashley Tharp
# @date: 01/02/2016

# Short Summary: 
# 	Sets the install names of the dynamic library dependencies of an executable

# Some Background:
# 	This script exists because of the way dylibs work and the fact that we have external dylibs linking at runtime to our app.
# 	Every dylib has a string called it's 'install name'. Every dylib will also have a list of rpaths.
# 	When we link with a 3rd party lib, we have to set the install name and rpaths 
# 	ourself because there is no possible way the the third party devs could know how our project is set up.  

# 	This script is included in the build process because the install names on dylibs can get messed up sometimes.  
# 	Sometimes when transferring between computers, if the path to a dependency was not made relative using @rpath or, 
# 	what I have decided to do, @loader_path, the dependency can't be found at run time.  As well, I will say sometimes the
# 	finder appears to do things under the hood that I am not aware of and has messed up my dylibs before. I think it may be 
# 	resetting the owner of the dylibs, but nonetheless, I have found the only safe way to move them is using
# 	the terminal. This point of failure means any unknowing dev could mess them up quite easily, and probably will, so this
# 	script being in the build process means that they can always just build a new .app if they messed up one by digging around
# 	in the .app file.


# 	So let's talk about dylibs again.  The install name is the path to where the dylib itself is.

# 	The install name is an rpath.  
# 	An rpath, is a runtime search path.
# 	A runtime search path, is added to a list of runtime search paths, that the application executable will 
# 	use to find it's dependencies.  
# 	The dylibs install name is a path to the dylib itself.
# 	You can set it with the -id tag using the install_name_tool



# 	This can get rather complicated because dependencies can have dependencies, which can have depencies of dependencies,
# 	so, a wise thing to do might be to put all your dependencies in the same folder so that you can set all the rpaths to
# 	point to the same directory and you don't have to worry about being clever.

# 	So, a dylib will have an install name, as well as a list of rpaths to it's dependencies.  This script sets those
# 	rpaths using install_name_tool -change.

# 	otool -L is returns the child depencies of any dylib.

def get_deps path_to_lib
	deps = `otool -L "#{path_to_lib}"`	
	deps_list = deps.split("\n")
	if deps_list.length > 0
		deps_list.drop(0) # if there is more than 0 dependencies, drop the first one, because the first dependency is always the lib pointing to itself
	end
	return deps_list
end

# this basically redirects all the dylibs to look in new_relative_dir to look for all the other dylibs
def fix_deps path_to_lib, deps, new_relative_dir
	deps.each do |dep|
		#d = dep.strip().split(' ')[0]
		#puts "gonna fix dep #{dep}"
		d = dep.gsub("\t", "")		
		dep = dep.gsub(/\(.*\)/, "")

		#puts "dep after string cleanup #{d}"

		if (d =~ /^@/) == nil && (d =~ /^\//) == nil #if it doesn't start with @ or /
			from = "#{d}"
			to = "#{new_relative_dir}/#{d}"
			#puts "\tfixing dependency #{from} => #{to}"
			`install_name_tool -change "#{from}" "#{to}" "#{path_to_lib}"`

		elsif "#{d}".include?("@rpath") || "#{d}".include?("@executable_path")
			from = "#{d}"
			to = "#{d}"
			to = to.gsub("@rpath/", "#{new_relative_dir}")
			to = to.gsub("@executable_path/", "#{new_relative_dir}")
			#puts "\tfixing dependency '#{from}' => '#{to}'"
			#puts "\t\t\tinstall_name_tool -change #{from} #{to} #{path_to_lib}"
			`install_name_tool -change "#{from}" "#{to}" "#{path_to_lib}"`
			# `install_name_tool -change "#{from}" "#{to}" "../MacOS/Filter\ Studio"`
		else
			#puts "do nothing for #{d}"
		end
	end
end

def get_levels_up_string num_levels
	i = 0
	levels_up_string = ""
	while i < num_levels do
		levels_up_string += "../"
		i += 1
	end
	return levels_up_string
end

# Note: this function assumes that the script is currently in the top level root dir of the .app file
def get_nodes(path_to_root)
	#puts "path_to_root: #{path_to_root}"
	#puts "pwd: #{`pwd`}"
	nodes = Dir.glob("*").select{|f| File.directory? f}	
	puts "nodes: #{nodes}"
	return nodes
end

def get_libs(path_to_root)
	libs = Dir.glob("*.dylib")
	return libs
end

def fix_node_libs path_to_root

	Dir.chdir("#{path_to_root}\/Contents\/Frameworks\/")
	libs = get_libs(path_to_root)
	Dir.chdir(".\/..\/..\/")
	#puts "pwd: #{`pwd`}"

	Dir.chdir(".\/Contents\/MacOS\/")
	nodes = get_nodes(path_to_root)
	#nodes = Dir.entries(".")
	Dir.chdir(".\/..\/..\/")

	nodes.each do |node|
		libs.each do |lib|
			`install_name_tool -change "#{lib}" "@loader_path\/..\/..\/Frameworks\/#{lib}" ".\/Contents\/MacOS\/#{node}/lib#{node}.dylib"`
		end
	end
	Dir.chdir(".\/..\/")
end

def get_folder_depth_from_macOS path

	# make a deep copy so we don't alter the path passed in
	newpath = Marshal.load(Marshal.dump(path))

	if  newpath.include? "MacOs"
		# if the path includes  MacOs/ we are going to count the number of slashes after that
		# we remove the optional end slash if there is one
		if newpath[-1] == "/"
			newpath[newpath.length - 1] = ""
		end
		if newpath[-2] == "/"
			newpath[newpath.length - 2] = ""
		end
		#puts "had path #{path} before removing MacOs"
		newpath = newpath.sub!(/.*?(?=MacOs\/)/im, "")
		newnewpath = newpath.sub("MacOs/", "")
		#puts "got path #{path} after removing MacOs"
		num_levels = newnewpath.scan(/(?=#{"\/"})/).count + 1
		return num_levels
	else 
		return -1
	end
end

# walk into every subdir in this dir and execute func inside that dir
def directory_walk path_to_dir


  Dir.foreach(path_to_dir) do |current_file|
    path = File.join(path_to_dir, current_file)
    if current_file == "." or current_file == ".."
      next
    elsif File.directory?(path)
      puts "got folder #{path}" # remove this line if you want; just prints directories      
      directory_walk(path)
    elsif(File.extname(current_file) == ".dylib")
      	puts "got #{current_file}"
      	#puts "calling get_deps(#{path})"
      	deps = get_deps(path)
      	#puts "got deps: #{deps}"

      	# for 1 level returns  ../ for 2 levels, returns ../../ and so on
      	current_folder_depth = get_folder_depth_from_macOS(path)
      	levels_up_string = get_levels_up_string(current_folder_depth) 
      	#puts "current_folder_depth: #{current_folder_depth} levels_up_string: #{levels_up_string}"

      	fix_deps(	path, deps, "@loader_path/#{levels_up_string}Frameworks/")
    end
  end
end

if __FILE__ == $0

	#if ARGV.length != 1
	#	puts "ERROR: incorrect number of arguments. This program takes a .app file as its single argument"

	if File.extname(ARGV[0]) == ".app"
		puts "ERROR: incorrect file type. This program only takes files of type .app"
	end
	

		# fix the install paths for all the dependencies (dylibs) in the Frameworks folder
		libs = get_libs("ARGV[0]/Contents/Frameworks")

		libs.each do |lib|
			puts "fixing '#{lib}'"
	 		deps = get_deps(lib)
	 		fix_deps(lib, deps, "@loader_path/Frameworks/")
	 	end

	 	# fix the install paths for the dependencies of the application binary itself
	 	binary_name = "#{ARGV[0]}".slice! ".app"
	 	puts "binary_name: #{binary_name}"
	 	fs_deps = get_deps(ARGV[0])
	 	fix_deps("#{ARGV[0]}/Contents/MacOS/#{binary_name}", fs_deps, "@loader_path/../../Frameworks/")

		# fix the dependencies for the files inside the node folders  in Contents/MacOs
		fix_node_libs(ARGV[0])

end

	# if File.directory? ARGV[0]  # if arg is a dir we fix the install names for all the dylibs in that dir
	# 	libs = get_libs(ARGV[0])

	# 	libs.each do |lib|
	# 		puts "fixing '#{lib}'"
	# 		deps = get_deps(lib)
	# 		fix_deps(lib, deps)
	# 	end
	# elsif File.file? ARGV[0] # otherwise we fix the install names of the executable given
	# 	fs_deps = get_deps(ARGV[0])
	# 	fix_deps(ARGV[0], fs_deps)
	# end
