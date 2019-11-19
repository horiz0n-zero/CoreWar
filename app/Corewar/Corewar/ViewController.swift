//
//  ViewController.swift
//  Corewar
//
//  Created by Antoine Feuerstein on 18/11/2019.
//  Copyright © 2019 Antoine Feuerstein. All rights reserved.
//

import Cocoa

class Libcorewar: NSObject {
    
    enum LibcorewarError: Error {
        case content(String)
        var localizedDescription: String {
            switch self {
            case .content(let txt):
                return txt
            }
        }
    }
    
    func getSrc(named name: String) throws -> s_libcorewar_src_file {
        var error: UnsafeMutablePointer<Int8>? = nil
        let named = name.cString(using: .utf8)!
        let srcFile: UnsafeMutablePointer<s_libcorewar_src_file>? = libcorewar_get_src_file(named, &error)
        
        if error != nil {
            throw LibcorewarError.content(String(cString: error!))
        }
        return srcFile!.pointee
    }
    
}

class ViewController: NSViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        
    }

}

