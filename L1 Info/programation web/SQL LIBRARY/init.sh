export PGHOST=/tmp/$LOGNAME
export PGPORT=$UID

/usr/lib/postgresql/11/bin/pg_ctl -D /tmp/$LOGNAME/ -l /tmp/$LOGNAME/startup.log initdb

pg_conftool -v /tmp/$LOGNAME/postgresql.conf set unix_socket_directories /tmp/$LOGNAME

