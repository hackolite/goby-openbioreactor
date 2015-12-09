from plan import Plan

cron = Plan()

cron.command('python /home/pi/motor.py -m motor4 -t 5 ', every='1.hour')
cron.command('python /home/pi/motor.py -m motor2 -t 5 ', every='1.hour')
cron.command('python /home/pi/motor.py -m motor1 -t 20 ', every='1.hour')

if __name__ == '__main__':
    cron.run('write')

