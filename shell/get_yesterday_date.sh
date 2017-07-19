
function get_yesterday_date() {
    local now=`date +%s`
    local a_day=`expr 24 \* 60 \* 60`
    local yesterday=`expr $now - $a_day`
    # echo $yesterday
    date -d@$yesterday +%Y%m%d
}

