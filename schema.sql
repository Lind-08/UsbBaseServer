CREATE TABLE host (
    id     INTEGER PRIMARY KEY AUTOINCREMENT
                   NOT NULL,
    secret TEXT,
    name   TEXT
);

CREATE TABLE usb (
    id     INTEGER PRIMARY KEY AUTOINCREMENT
                   NOT NULL,
    VID    TEXT,
    PID    TEXT,
    serial TEXT,
    name   TEXT
);

CREATE TABLE rules (
    id      INTEGER PRIMARY KEY AUTOINCREMENT
                    NOT NULL,
    host_id INTEGER REFERENCES host (id) ON DELETE CASCADE
                                         ON UPDATE CASCADE,
    usb_id  INTEGER REFERENCES usb (VID) ON DELETE CASCADE
                                         ON UPDATE CASCADE,
    value   BOOLEAN DEFAULT FALSE
);