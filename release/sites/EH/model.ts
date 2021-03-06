export const source: ISource = {
    name: "E-Hentai",
    modifiers: [],
    auth: {},
    apis: {
        html: {
            name: "Regex",
            auth: [],
            forcedLimit: 25,
            search: {
                url: (query: any, opts: any, previous: any): string => {
                    return "/?page=" + (query.page - 1) + "&f_search=" + query.search;
                },
                parse: (src: string): IParsedSearch => {
                    // Gallery mode regex: <div class="id1"[^>]*><div class="id2"><a href="(?<url>[^"]+)">(?<name>[^<]+)<\/a><\/div><div class="id3"[^>]*><a[^>]*><img src="(?<preview_url>[^"]*)"[^>]*><\/a><\/div><div class="id4"><div class="id41"[^>]* title="(?<category>[^"]*)"><\/div><div class="id42">(?<images_count>[0-9,]+) files<\/div>
                    const matches = Grabber.regexMatches('<tr class="gtr\\d"><td[^>]*><a[^>]*><img[^>]*alt="(?<category>[^"]*)"[^>]*></a></td><td[^>]*>(?<date>[^<]*)</td><td[^>]*><div[^>]*><div class="it2" id="i(?<id>\\d+)"[^>]*>(?:<img src="(?<preview_url>[^"]+)"[^>]*>|(?<encoded_thumbnail>[^<]*))</div><div class="it3">.*?</div><div class="it5"><a href="(?<url>[^"]+)"[^>]*>(?<name>[^<]*)</a></div><div class="it4">.*?</div></div></div></td><td[^>]*><div><a[^>]*>(?<uploader>[^<]*)</a></div></td></tr>', src);
                    const images = matches.map((match: any) => {
                        match["type"] = "gallery";
                        if ("encoded_thumbnail" in match && match["encoded_thumbnail"].length > 0) {
                            const parts = match["encoded_thumbnail"].split("~");
                            const protocol = parts[0] === "init" ? "http://" : "https://";
                            match["preview_url"] = protocol + parts[1] + "/" + parts[2];
                            delete match["encoded_thumbnail"];
                        }
                        return match;
                    });
                    return {
                        images,
                        pageCount: Grabber.countToInt(Grabber.regexToConst("page", ">...</td><td[^>]*><a[^>]*>(?<page>\\d+)</a></td>", src)),
                        imageCount: Grabber.countToInt(Grabber.regexToConst("count", ">Showing \\d+-\\d+ of (?<count>[0-9,]+)<", src)),
                    };
                },
            },
            gallery: {
                url: (id: number): IError => {
                    return { error: "Not supported (gallery token)" };
                },
                parse: (src: string): IParsedGallery => {
                    return {
                        images: Grabber.regexToImages('<div class="gdtm"[^>]*><div style="[^"]*background:transparent url\\((?<preview_url>[^)]+)\\) [^"]*"><a href="(?<page_url>[^"]+)"><img[^>]*></a></div>', src),
                    };
                },
            },
            details: {
                url: (id: number, md5: string): IError => {
                    return { error: "Not supported (view token)" };
                },
                parse: (src: string): IParsedDetails => {
                    // Grabber.regexMatches("<div>(?<filename>[^:]*) :: (?<width>\d+) x (?<height>\d+) :: (?<filesize>[^ ]+ [KM]B)<\/div>", src);
                    return {
                        imageUrl: Grabber.regexToConst("url", '<img id="img" src="(?<url>[^"]+)"', src),
                    };
                },
            },
        },
    },
};
