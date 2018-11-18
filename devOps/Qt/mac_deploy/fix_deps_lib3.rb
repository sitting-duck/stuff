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



def get_libs path
	return Dir.glob("#{path}/*.dylib")
end

def get_deps path_to_lib
	deps = `otool -L "#{path_to_lib}"`
	return deps.split("\n")
end

def fix_deps path_to_lib, deps
	deps.each do |dep|
		d = dep.strip().split(' ')[0]
		if (d =~ /^@/) == nil && (d =~ /^\//) == nil
			from = "#{d}"
			to = "@loader_path/../Frameworks/#{d}"
			puts "\tfixing dependency '#{from}' => '#{to}'"
			`install_name_tool -change "#{from}" "#{to}" "#{path_to_lib}"`
		end

		if "#{d}".include?("@rpath") || "#{d}".include?("@executable_path")
			from = "#{d}"
			to = "#{d}"
			to = to.gsub("@rpath/", "@loader_path/../Frameworks/")
			to = to.gsub("@executable_path/", "@loader_path/../Frameworks/")
			#puts "\tfixing dependency '#{from}' => '#{to}' for: #{path_to_lib}"
			`install_name_tool -change "#{from}" "#{to}" "#{path_to_lib}"`
			# `install_name_tool -change "#{from}" "#{to}" "../MacOS/Filter\ Studio"`
		end

		if "#{d}".include?("usr/local/lib/")
			from = "#{d}"
			to = "#{d}"
			to = to.gsub("usr/local/lib/", "@loader_path/../Frameworks/")
			#puts "\tfixing dependency '#{from}' => '#{to}' for: #{path_to_lib}"
			`install_name_tool -change "#{from}" "#{to}" "#{path_to_lib}"`
		end

		if "#{d}".include?("/usr/local/opt/minizip/lib/")
			from = "#{d}"
			to = "#{d}"
			to = to.gsub("/usr/local/opt/minizip/lib/", "@loader_path/../Frameworks/")
			puts "\tfixing dependency '#{from}' => '#{to}' for: #{path_to_lib}"
			`install_name_tool -change "#{from}" "#{to}" "#{path_to_lib}"`
		end

	end
end

def fix_deps_for_dylib path_to_lib, deps
	deps.each do |dep|
		d = dep.strip().split(' ')[0]
		if (d =~ /^@/) == nil && (d =~ /^\//) == nil
			from = "#{d}"
			to = "@loader_path/#{d}"
			puts "\tfixing dependency '#{from}' => '#{to}'"
			`install_name_tool -change "#{from}" "#{to}" "#{path_to_lib}"`
		end

		if "#{d}".include?("@rpath") || "#{d}".include?("@executable_path")
			from = "#{d}"
			to = "#{d}"
			to = to.gsub("@rpath/", "@loader_path/")
			to = to.gsub("@executable_path/", "@loader_path/")
			#puts "\tfixing dependency '#{from}' => '#{to}' for: #{path_to_lib}"
			`install_name_tool -change "#{from}" "#{to}" "#{path_to_lib}"`
			# `install_name_tool -change "#{from}" "#{to}" "../MacOS/Filter\ Studio"`
		end

		if "#{d}".include?("/usr/local/lib/")
			from = "#{d}"
			to = "#{d}"
			to = to.gsub("/usr/local/lib/", "@loader_path/")
			#puts "\tfixing dependency '#{from}' => '#{to}' for: #{path_to_lib}"
			`install_name_tool -change "#{from}" "#{to}" "#{path_to_lib}"`
		end

		if "#{d}".include?("/usr/local/opt/minizip/lib/")
			from = "#{d}"
			to = "#{d}"
			to = to.gsub("/usr/local/opt/minizip/lib/", "@loader_path/")
			puts "\tfixing dependency '#{from}' => '#{to}' for: #{path_to_lib}"
			`install_name_tool -change "#{from}" "#{to}" "#{path_to_lib}"`
		end

	end
end

if __FILE__ == $0
	puts "to fix: #{ARGV[0]}"
	
	if File.directory? ARGV[0]  # if arg is a dir we fix the install names for all the dylibs in that dir
		libs = get_libs(ARGV[0])

		libs.each do |lib|
			#puts "fixing '#{lib}'"
			deps = get_deps(lib)
			fix_deps_for_dylib(lib, deps)
		end
	elsif File.file? ARGV[0] # otherwise we fix the install names of the executable given
		fs_deps = get_deps(ARGV[0])
		fix_deps(ARGV[0], fs_deps)
	end
end
