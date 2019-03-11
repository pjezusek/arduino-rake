FQBN = 'arduino:avr:uno'
BUILD_DIR = File.absolute_path('build')
CACHE_DIR = File.absolute_path('build/cache')
DEV_TTY = '/dev/ttyACM0'

OUTPUT_FILE = File.absolute_path("#{BUILD_DIR}/output.hex")
TTY_TARGET_CONFIG = '1:0:1cb2:80:3:1c:7f:15:4:0:1:0:11:13:1a:0:12:f:17:16:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0'
TTY_CONFIG_PARAMS = %w(
  cs8
  115200
  ignbrk
  -brkint
  -icrnl
  -imaxbel
  -opost
  -onlcr
  -isig
  -icanon
  -iexten
  -echo
  -echoe
  -echok
  -echoctl
  -echoke
  noflsh
  -ixon
  -crtscts
)

namespace :arduino do

  desc 'clean dest directory'
  task :clean do
    sh "rm -rf #{BUILD_DIR}/*" if Dir.exist? BUILD_DIR
  end

  desc 'rebuild and upload program'
  task install: [:rebuild, :upload]

  desc 'rebuild program'
  task rebuild: [:clean, :build]

  desc 'compile project'
  task build: OUTPUT_FILE

  file OUTPUT_FILE do
    sh "mkdir #{BUILD_DIR}" unless Dir.exist? BUILD_DIR
    sh "mkdir #{CACHE_DIR}" unless Dir.exist? CACHE_DIR
    sh "arduino-cli compile --fqbn #{FQBN} --build-path #{BUILD_DIR} --build-cache-path #{CACHE_DIR}\\
        --output #{OUTPUT_FILE}"
  end

  desc 'upload program to board'
  task upload: OUTPUT_FILE do
    sh "arduino-cli upload -p #{DEV_TTY} --fqbn #{FQBN} -i #{OUTPUT_FILE}"
  end

  desc 'check tty connection'
  task :check_tty do
    if File.exist? DEV_TTY 
      puts "#{DEV_TTY} exists"
    else
      puts "#{DEV_TTY} does not exist"
      next # stop task
    end

    readable = File.stat(DEV_TTY).readable?
    if readable
      puts "can read from #{DEV_TTY}"
    else
      puts "cannot read from #{DEV_TTY}"
    end

    writable = File.stat(DEV_TTY).writable?
    if writable
      puts "can write to #{DEV_TTY}"
    else
      puts "cannot write to #{DEV_TTY}"
    end

    next unless writable && readable

    if %x(stty -F #{DEV_TTY} -g).strip == TTY_TARGET_CONFIG
      puts "#{DEV_TTY} configured properly"
    else
      puts "wrong configuration of #{DEV_TTY}"
    end
  end

  desc 'configure tty'
  task :configure_tty do
    exist = File.exist? DEV_TTY
    readable = File.stat(DEV_TTY).readable?
    writable = File.stat(DEV_TTY).writable?

    if exist && readable && writable
      sh "stty -F #{DEV_TTY} #{TTY_CONFIG_PARAMS.join(' ')}"
      Rake::Task["arduino:check_tty"].invoke
    else
      puts "Problem with #{DEV_TTY}. Run rake arduino:check_tty for details"
    end
  end

  desc 'run screen session on tty'
  task :run do
    sh "screen #{DEV_TTY}"
  end
end

