require 'fileutils'
require 'set'
require 'optparse'

options = {}
OptionParser.new do |opts|
    opts.banner = "Usage: example.rb [options]"

    opts.on("-s", "--src SRCDIR", "source patch directory") do |v|
        options[:src] = v
    end

    opts.on("-d", "--dest DESTDIR", "cluster destination directory") do |v|
        options[:dest] = v
    end

    opts.on("-a", "--assign FILENAME", "assignment list file") do |v|
        options[:assign] = v
    end

    opts.on("-h", "--help", "Prints this help") do
        puts opts
        exit
    end
end.parse!

srcfolder = options[:src]
desfolder = options[:dest]
clulist = options[:assign]

puts "Collecting imgs from #{ srcfolder } to #{ desfolder } acording to #{clulist} ..."
set = Set.new


if !File.directory?(desfolder)
    FileUtils.mkdir(desfolder)
end


IO.foreach(clulist).with_index do|c,i|
    ci = c.to_i;
    subdir = "#{desfolder}/#{ci}".chomp
    if !set.include?(ci)
        begin
            FileUtils.mkdir_p(subdir)
        rescue => e
            print e.message
            print e.backtrace.join("\n")
        end
        set<<ci;
    end;
    zero_padded_name = format("%06d",i+1)
    FileUtils.cp "#{srcfolder}/#{zero_padded_name}.jpg", subdir
end

