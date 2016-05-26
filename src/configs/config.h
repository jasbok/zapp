#ifndef config_H
#define config_H

#include <QString>

class config
{
public:
    static config& instance(){
        static config config;
        return config;
    }

    QString source() const;
    QString container() const;
    QString target() const;
    QString user() const;
    QString innoextract_bin() const;
    QString dosbox_bin() const;


private:
    QString _source;
    QString _container;
    QString _target;
    QString _user;
    QString _innoextract_bin;
    QString _dosbox_bin;

    config();
    config(config&& config);
    config(const config& config);
    ~config(){}

    const config &operator=(const config& config);
    const config &operator=(config&& config);

    void _parse_args();
    void _calculate_paths();
};

#endif // config_H
