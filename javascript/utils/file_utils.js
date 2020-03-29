
// converts a QUrl from QML code into a usable file path
function get_file_path_from_url(qurl) {

    qurl = qurl.split('%5C').join('\\');
    qurl = qurl.split('\\').join('/');
    return qurl;

}

// A user may pass a QUrl in QML code, and that url may be a file path on a Mac machine
function is_mac_qurl(qurl) {

    return fileUrl[1] != ":";

}

